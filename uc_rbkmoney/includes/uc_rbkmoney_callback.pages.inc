<?php

/**
 * Callback URL for RBKmoney server response
 *
 * @see https://rbkmoney.github.io/webhooks-events-api/
 */
function uc_rbkmoney_callback_result()
{
    $type = 'callback_result';
    $content = file_get_contents('php://input');
    _uc_rbkmoney_logger($type, "<pre>%logs</pre>", ['%logs' => var_export(['content' => $content], TRUE)]);

    if (empty($_SERVER[SIGNATURE])) {
        http_response_code(HTTP_CODE_BAD_REQUEST);
        _uc_rbkmoney_logger($type, "Missing signature. <pre>%logs</pre>", ['%logs' => var_export([$content], TRUE)]);
        exit();
    }

    $params_signature = _uc_rbkmoney_get_parameters_content_signature($_SERVER[SIGNATURE]);
    if (empty($params_signature[SIGNATURE_ALG])) {
        _uc_rbkmoney_logger($type, "Missing required parameter " . SIGNATURE_ALG . " signature. <pre>%logs</pre>", ['%logs' => var_export([$content], TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    if (empty($params_signature[SIGNATURE_DIGEST])) {
        _uc_rbkmoney_logger($type, "Missing required parameter " . SIGNATURE_DIGEST . " signature. <pre>%logs</pre>", ['%logs' => var_export([$content], TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    $signature = _uc_rbkmoney_urlsafe_b64decode($params_signature[SIGNATURE_DIGEST]);
    if (!_uc_rbkmoney_verification_signature($content, $signature, MERCHANT_CALLBACK_PUBLIC_KEY)) {
        _uc_rbkmoney_logger($type, "Signature did not match. <pre>%logs</pre>",
            ['%logs' => var_export([
                $_SERVER[SIGNATURE],
                $content,
                $signature,
                MERCHANT_CALLBACK_PUBLIC_KEY
            ], TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        echo json_encode(array('message' => 'Signature did not match'));
        exit();
    }

    $required_fields = [INVOICE, EVENT_TYPE];
    $data = json_decode($content, TRUE);

    foreach ($required_fields as $field) {
        if (empty($data[$field])) {
            _uc_rbkmoney_logger($type, "Missing required fields. <pre>%logs</pre>",
                ['%logs' => var_export([
                    'input_content' => $content,
                    'required_fields' => $required_fields
                ], TRUE)]);
            http_response_code(HTTP_CODE_BAD_REQUEST);
            echo json_encode(array('message' => 'Missing required fields'));
            exit();
        }
    }

    $current_shop_id = (int)variable_get('uc_rbkmoney_shop_id');
    if ($data[INVOICE][INVOICE_SHOP_ID] != $current_shop_id) {
        _uc_rbkmoney_logger($type, INVOICE_SHOP_ID . ' не совпадает . <pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        echo json_encode(array('message' => INVOICE_SHOP_ID . ' did not match'));
        exit();
    }

    if (empty($data[INVOICE][INVOICE_METADATA][ORDER_ID])) {
        _uc_rbkmoney_logger($type, 'Missing ' . ORDER_ID . '. <pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        echo json_encode(array('message' => 'Missing ' . ORDER_ID));
        exit();
    }

    $order_id = $data[INVOICE][INVOICE_METADATA][ORDER_ID];
    $order = uc_order_load($order_id);
    $order_amount = _uc_rbkmoney_prepare_amount($order->order_total);
    $invoice_amount = $data[INVOICE][INVOICE_AMOUNT];
    if ($order_amount != $invoice_amount) {
        _uc_rbkmoney_logger($type, 'The amount does not match the order amount <pre>%logs</pre>', ['%logs' => var_export($content, TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        echo json_encode(array('message' => 'The amount does not match the order amount '));
        exit();
    }

    $allowed_event_types = [EVENT_TYPE_INVOICE_PAID, EVENT_TYPE_INVOICE_CANCELLED];
    if (in_array($data[EVENT_TYPE], $allowed_event_types)) {
        $invoice_status = $data[INVOICE][INVOICE_STATUS];
        _uc_rbkmoney_update_status_order($order_id, $invoice_status);
    }

    exit();
}

function _uc_rbkmoney_urlsafe_b64decode($string)
{
    $data = str_replace(array('-', '_'), array('+', '/'), $string);
    $mod4 = strlen($data) % 4;
    if ($mod4) {
        $data .= substr('====', $mod4);
    }
    return base64_decode($data);
}

function _uc_rbkmoney_urlsafe_b64encode($string)
{
    $data = base64_encode($string);
    return str_replace(array('+', '/'), array('-', '_'), $data);
}

function _uc_rbkmoney_get_parameters_content_signature($content_signature)
{
    preg_match_all(SIGNATURE_PATTERN, $content_signature, $matches, PREG_PATTERN_ORDER);
    $params = array();
    $params[SIGNATURE_ALG] = $matches[1][0];
    $params[SIGNATURE_DIGEST] = $matches[2][0];
    return $params;
}

function _uc_rbkmoney_verification_signature($data = '', $signature = '', $public_key = '')
{
    if (empty($data) || empty($signature) || empty($public_key)) {
        return FALSE;
    }

    $public_key_id = openssl_get_publickey($public_key);
    if (empty($public_key_id)) {
        return FALSE;
    }

    $verify = openssl_verify($data, $signature, $public_key_id, OPENSSL_SIGNATURE_ALG);
    return ($verify == OPENSSL_VERIFY_SIGNATURE_IS_CORRECT);
}

<?php

/**
 * Callback URL for RBKmoney server response
 */
function uc_rbkmoney_callback_result()
{
    if(empty($_SERVER[SIGNATURE])) {
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    $type = 'callback_result';
    $content = file_get_contents('php://input');
    _uc_rbkmoney_logger($type, "<pre>%logs</pre>", ['%logs' => var_export($content, TRUE)]);

    $required_fields = [INVOICE_ID, PAYMENT_ID, AMOUNT, CURRENCY, CREATED_AT, METADATA, STATUS];
    $data = json_decode($content, TRUE);
    foreach ($required_fields as $field) {
        if (empty($data[$field])) {
            _uc_rbkmoney_logger($type, "Отсутствуют обязательные поля. <pre>%logs</pre>",
                ['%logs' => var_export([
                    'input_content' => $content,
                    'required_fields' => $required_fields
                ], TRUE)]);
            http_response_code(HTTP_CODE_BAD_REQUEST);
            exit();
        }
    }

    if (empty($data[METADATA][ORDER_ID])) {
        _uc_rbkmoney_logger($type, 'Отсутствует ' . ORDER_ID . ". <pre>%logs</pre>", ['%logs' => var_export($content, TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    if (!$signature = base64_decode($_SERVER[SIGNATURE], TRUE)) {
        _uc_rbkmoney_logger($type, "Не удалось декодировать сигнатуру. <pre>%logs</pre>",
            ['%logs' => var_export(
                [
                    'content' => $content,
                    SIGNATURE => $_SERVER[SIGNATURE],
                ], TRUE)
            ]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    if (!verification_signature($content, $signature, MERCHANT_CALLBACK_PUBLIC_KEY)) {
        _uc_rbkmoney_logger($type, "Сигнатура не совпала. <pre>%logs</pre>",
            ['%logs' => var_export([
                $content,
                $signature,
                MERCHANT_CALLBACK_PUBLIC_KEY
            ], TRUE)]);
        http_response_code(HTTP_CODE_BAD_REQUEST);
        exit();
    }

    $order_id = $data[METADATA][ORDER_ID];
    $invoice_status = $data[STATUS];
    _uc_rbkmoney_update_status_order($order_id, $invoice_status);
    exit();
}

function verification_signature($data = '', $signature = '', $public_key = '')
{
    if (empty($data) || empty($signature) || empty($public_key)) {
        return FALSE;
    }

    $public_key_id = openssl_get_publickey($public_key);
    if (empty($public_key_id)) {
        return FALSE;
    }

    $verify = openssl_verify($data, $signature, $public_key_id, OPENSSL_ALGO_SHA256);
    return ($verify == OPENSSL_VERIFY_SIGNATURE_IS_CORRECT);
}

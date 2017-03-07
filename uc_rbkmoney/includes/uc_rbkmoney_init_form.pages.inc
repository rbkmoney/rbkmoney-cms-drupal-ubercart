<?php

/**
 * Init payment
 */
function uc_rbkmoney_init_form_info()
{
    header('Access-Control-Allow-Origin: *');
    header('Access-Control-Allow-Methods: PUT, POST, GET, OPTIONS');
    header('Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept, Authorization, X-Request-ID');

    if ($_SERVER['REQUEST_METHOD'] == HTTP_METHOD_OPTIONS) {
        http_response_code(HTTP_CODE_OK);
        exit();
    }

    $body = file_get_contents('php://input');
    _uc_rbkmoney_logger('init_payment_req', "<pre>%logs</pre>", ['%logs' => var_export($body, TRUE)]);
    $request = json_decode($body, TRUE);
    
    if(!isset($request['invoiceId'])) {
        throw new Exception('Not found required parameter invoiceId');
    }

    $headers = [];
    $headers[] = 'X-Request-ID: ' . uniqid();
    $headers[] = 'Authorization: Bearer ' . MERCHANT_PRIVATE_KEY;
    $headers[] = 'Content-type: application/json; charset=utf-8';
    $headers[] = 'Accept: application/json';

    $data = [
        'paymentToolToken' => $request['token'],
        'paymentSession' => $request['session'],
        'contactInfo' => [
            'email' => !empty($request['contactInfo']['email']) ? $request['contactInfo']['email'] : '',
        ]
    ];
    $json = json_encode($data);

    $url = _uc_rbkmoney_prepare_api_url('invoices/' . $request['invoiceId'] . '/payments');
    $response = _uc_rbkmoney_send($url, HTTP_METHOD_POST, $headers, $json, 'init_payment');

    http_response_code($response['http_code']);
    print $response['body'];
    exit();
}

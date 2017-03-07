<?php

/**
 * Prints the response invoice status
 */
function uc_rbkmoney_status_info()
{
    header('Access-Control-Allow-Origin: *');
    header('Access-Control-Allow-Methods: PUT, POST, GET, OPTIONS');
    header('Access-Control-Allow-Headers: Origin, X-Requested-With, Content-Type, Accept, Authorization, X-Request-ID');

    _uc_rbkmoney_logger('status_req', "<pre>%logs</pre>", ['%logs' => var_export($_GET, TRUE)]);
    if(!isset($_GET['invoiceId'])) {
        throw new Exception('Not found required parameter invoiceId');
    }

    if(!isset($_GET['orderId'])) {
        throw new Exception('Not found required parameter orderId');
    }


    $headers = [];
    $headers[] = 'X-Request-ID: ' . uniqid();
    $headers[] = 'Authorization: Bearer ' . MERCHANT_PRIVATE_KEY;

    $query_params = [];
    $query_params['limit'] = (!empty($_GET['limit'])) ? $_GET['limit'] : POLLING_STATUSES_LIMIT;
    if (!empty($_GET['eventID'])) {
        $query_params['eventID'] = $_GET['eventID'];
    }

    $url = _uc_rbkmoney_prepare_api_url('processing/invoices/' . $_GET['invoiceId'] . '/events', $query_params);
    $response = _uc_rbkmoney_send($url, HTTP_METHOD_GET, $headers, '', 'polling_status');

    $events = drupal_json_decode($response['body']);
    if(!empty($events)) {
        $last_event = $events[count($events) - 1];
        $event_type = $last_event['eventType'];

        switch ($event_type) {
            case 'EventInvoiceStatusChanged':
            case 'EventPaymentStatusChanged':
                $status = $last_event['status'];
                break;
            default:
                $status = 'unknown';
        }

        $allowed_statuses = ['paid', 'failed', 'cancelled'];
        if (in_array($status, $allowed_statuses)) {
            _uc_rbkmoney_update_status_order($_GET['orderId'], $status);
        }
    }

    http_response_code($response['http_code']);
    print $response['body'];
    exit();
}

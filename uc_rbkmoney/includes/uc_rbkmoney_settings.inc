<?php

/**
 * Define payment statuses
 */
define('UC_RBKMONEY_STATUS_FAILED', 'cancelled');
define('UC_RBKMONEY_STATUS_SUCCESS', 'paid');

define('ANONYMOUS_USER_ID', 0);

/**
 * Module data
 */
define('MODULE_NAME', 'uc_rbkmoney');
define('MODULE_BASE_PATH', base_path() . drupal_get_path('module', MODULE_NAME));

/**
 * Api URL
 */
define('API_URL', 'https://api.rbk.money/v1/');

/**
 * Merchant settings
 */
define('MERCHANT_PRIVATE_KEY', trim(variable_get('uc_rbkmoney_merchant_private_key', 'merchant_private_key')));
define('MERCHANT_CALLBACK_PUBLIC_KEY', trim(variable_get('uc_rbkmoney_merchant_callback_public_key', 'merchant_callback_public_key')));

/**
 * Payment form
 */
define('BASE_URL', $GLOBALS['base_url']);
define('PAYMENT_FORM_URL', 'https://checkout.rbk.money/checkout.js');
define('PAYMENT_FORM_SUCCESS_URL', BASE_URL . '/uc_rbkmoney/success');
define('PAYMENT_FORM_PATH_IMG_LOGO', BASE_URL . MODULE_BASE_PATH . '/images/logo_default.png');

/**
 * Payment method logo
 */
define('PAYMENT_METHOD_PATH_IMG_LOGO', MODULE_BASE_PATH . '/images/logo_rbkmoney.png');

/**
 * Currency
 */
define('DEFAULT_CURRENCY', 'RUB');
define('CURRENT_CURRENCY', trim(variable_get('uc_rbkmoney_currency', DEFAULT_CURRENCY)));

/**
 * Create invoice settings
 */
define('CREATE_INVOICE_TEMPLATE_DUE_DATE', 'Y-m-d\TH:i:s\Z');
define('CREATE_INVOICE_DUE_DATE', '+1 days');

/**
 * Constants for Callback
 */

define('SIGNATURE', 'HTTP_CONTENT_SIGNATURE');
define('SIGNATURE_ALG', 'alg');
define('SIGNATURE_DIGEST', 'digest');
define('SIGNATURE_PATTERN', "|alg=(\S+);\sdigest=(.*)|i");


define('EVENT_TYPE', 'eventType');

// EVENT TYPE INVOICE
define('EVENT_TYPE_INVOICE_CREATED', 'InvoiceCreated');
define('EVENT_TYPE_INVOICE_PAID', 'InvoicePaid');
define('EVENT_TYPE_INVOICE_CANCELLED', 'InvoiceCancelled');
define('EVENT_TYPE_INVOICE_FULFILLED', 'InvoiceFulfilled');

// EVENT TYPE PAYMENT
define('EVENT_TYPE_PAYMENT_STARTED', 'PaymentStarted');
define('EVENT_TYPE_PAYMENT_PROCESSED', 'PaymentProcessed');
define('EVENT_TYPE_PAYMENT_CAPTURED', 'PaymentCaptured');
define('EVENT_TYPE_PAYMENT_CANCELLED', 'PaymentCancelled');
define('EVENT_TYPE_PAYMENT_FAILED', 'PaymentFailed');


define('INVOICE', 'invoice');
define('INVOICE_ID', 'id');
define('INVOICE_SHOP_ID', 'shopID');
define('INVOICE_STATUS', 'status');
define('INVOICE_DUE_DATE', 'dueDate');
define('INVOICE_AMOUNT', 'amount');
define('INVOICE_CURRENCY', 'currency');
define('INVOICE_REASON', 'reason');
define('INVOICE_METADATA', 'metadata');

define('ORDER_ID', 'order_id');

define('PAYMENT', 'payment');
define('PAYMENT_ID', 'id');
define('PAYMENT_AMOUNT', 'amount');
define('PAYMENT_CURRENCY', 'currency');
define('PAYMENT_STATUS', 'status');

/**
 * Api params
 */
define('API_INVOICE_ID', 'invoice_id');

/**
 * Openssl verify
 */
define('OPENSSL_VERIFY_SIGNATURE_IS_CORRECT', 1);
define('OPENSSL_VERIFY_SIGNATURE_IS_INCORRECT', 0);
define('OPENSSL_VERIFY_ERROR', -1);
define('OPENSSL_SIGNATURE_ALG', OPENSSL_ALGO_SHA256);

/**
 * HTTP CODE
 */
define('HTTP_CODE_OK', 200);
define('HTTP_CODE_CREATED', 201);
define('HTTP_CODE_MOVED_PERMANENTLY', 301);
define('HTTP_CODE_BAD_REQUEST', 400);
define('HTTP_CODE_INTERNAL_SERVER_ERROR', 500);

/**
 * HTTP METHOD
 */
define('HTTP_METHOD_GET', 'GET');
define('HTTP_METHOD_POST', 'POST');

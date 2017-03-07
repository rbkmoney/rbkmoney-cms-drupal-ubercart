<?php

/**
 * Define payment statuses
 */
define('UC_RBKMONEY_STATUS_FAILED', 'failed');
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
define('MERCHANT_PUBLIC_KEY', trim(variable_get('uc_rbkmoney_merchant_public_key', 'merchant_public_key')));
define('MERCHANT_CALLBACK_PUBLIC_KEY', trim(variable_get('uc_rbkmoney_merchant_callback_public_key', 'merchant_callback_public_key')));

/**
 * Payment form
 */
define('BASE_URL', $GLOBALS['base_url']);
define('PAYMENT_FORM_URL', 'https://checkout.rbk.money/payframe/payframe.js');
define('PAYMENT_FORM_INIT_URL', BASE_URL . '/uc_rbkmoney/form/init');
define('PAYMENT_FORM_STATUS_URL', BASE_URL . '/uc_rbkmoney/status');
define('PAYMENT_FORM_FAILED_URL', BASE_URL . '/uc_rbkmoney/rd/fail');
define('PAYMENT_FORM_SUCCESS_URL', BASE_URL . '/uc_rbkmoney/rd/success');
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
 * Polling Statuses
 */
define('POLLING_STATUSES_LIMIT', 10000);

/**
 * Constants for Callback
 */
define('INVOICE_ID', 'invoice_id');
define('PAYMENT_ID', 'payment_id');
define('AMOUNT', 'amount');
define('CURRENCY', 'currency');
define('CREATED_AT', 'created_at');
define('METADATA', 'metadata');
define('STATUS', 'status');
define('SIGNATURE', 'HTTP_X_SIGNATURE');
define('ORDER_ID', 'order_id');

/**
 * Openssl verify
 */
define('OPENSSL_VERIFY_SIGNATURE_IS_CORRECT', 1);
define('OPENSSL_VERIFY_SIGNATURE_IS_INCORRECT', 0);
define('OPENSSL_VERIFY_ERROR', -1);

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
define('HTTP_METHOD_OPTIONS', 'OPTIONS');

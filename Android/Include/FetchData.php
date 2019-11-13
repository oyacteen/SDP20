<?php

require_once dirname(__FILE__).'/DbOperation.php';

$response = array();

if($_SERVER['REQUEST_METHOD']=='GET') {
    $db = new DbOperation();
    $response[] = $db->getLastRow();
}
echo json_encode($response);

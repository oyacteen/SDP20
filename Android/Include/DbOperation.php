<?php

    class DbOperation{
        
        private $con;

        function __construct() {
            require_once dirname(__FILE__).'/DbConnect.php';
            $db = new DbConnect();
            $this->con = $db->connect();
        }

        function getLastRow(){
            $stmt = $this->con->prepare("SELECT * FROM plant_monitor ORDER BY date_time DESC limit 1");
            $stmt->execute();
            return $stmt->get_result()->fetch_assoc();
        }
    }
<?php
    class DbConnect {

        private $con;

        function __construct() {
        }
        
        function connect() {
            include_once dirname(__FILE__).'/Constant.php';
            $this->con = new mysqli(DB_HOST,DB_USER,DB_PASSWORD,DB_NAME);

            return $this->con;
        }
    }

<?php

$servername = "clover.cclls6i3ttha.us-east-2.rds.amazonaws.com";
$username = "clover";
$password = "clover1234";
$dbname = "clover";

$json_array = array();

$conn = mysqli_connect($servername, $username, $password, $dbname);
if($conn) {
echo "connection success";
}
else {
echo "connection not successful";
}

$sql = "SELECT * FROM plant_monitor ORDER BY date_time DESC limit 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
    while($row = $result->fetch_assoc()) {
        $json_array[] = $row;
    }
} else {
    echo "0 results";
}
$json_obj = json_encode($json_array);
print($json_obj);
$conn->close();
?>
<?php
require 'config.php';

$sql = "SELECT * FROM temperature_db ORDER BY id DESC";
$result = $db->query($sql);
if (!$result) {
    echo "Error: " . $sql . "<br>" . $db->error;
}

$rows = $result->fetch_assoc();

echo json_encode($rows);
?>

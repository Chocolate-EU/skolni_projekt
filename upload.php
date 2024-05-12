<?php

$servername = "localhost";
$username = "your_username";
$password = "your_password";
$dbname = "your_database";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$dogName = $_POST['dog_name'];
$startTime = $_POST['start_time'];
$endTime = $_POST['end_time'];

$sql = "INSERT INTO dog_races (dog_name, start_time, end_time) VALUES ('$dogName', '$startTime', '$endTime')";

if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
s
$conn->close();

?>

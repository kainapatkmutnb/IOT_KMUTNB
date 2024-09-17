<?php
define('DB_HOST', 'fdb1029.awardspace.net');
define('DB_USERNAME','4528030_kainapatdb');
define('DB_PASSWORD','Kainapat12');
define('DB_NAME','4528030_kainapatdb');

define('POST_DATA_URL','http://kainapatdb.atwebpages.com/sensordata.php');


define('PROJECT_API_KEY','kainapatmysqldht');

date_default_timezone_set('Asia/Bangkok');

$db = new mysqli(DB_HOST, DB_USERNAME , DB_PASSWORD , DB_NAME);


if ($db->connect_errno){
        echo "Connection to database is failed: ".$db->connect_error;
        exit();
// }else{
        //echo "Connected successfully";
}

?>
       
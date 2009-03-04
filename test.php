<?php

$dbh = new PDO("mysql:dbname=YOURDBNAME;host=127.0.0.1", "USERNAME", "PASSWORD");

$dbh->query('SET NAMES cp1250');

$stmt = $dbh->prepare("SELECT * FROM wp_1_posts");
$stmt->execute();
$result = $stmt->fetchAll(PDO::FETCH_ASSOC);

header('Content-type: text/xml; charset=windows-1250');

$cfoo = new PdoXml();
echo $cfoo->makeXML($result, true);

?>

<html>
    <head>
        <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $ean = $_REQUEST['ean'];
    $design = $_REQUEST['design'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        $sql = "UPDATE produto SET design = :design WHERE ean = :ean; ";
        $result = $db->prepare($sql);                         
        $result->execute([':design' => $design, ':ean' => $ean]);    

        echo("<p>Designação do produto alterada.</p>");  

        $db->query("commit;");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>ERROR: {$e->getMessage()}</p>");
    }
?>
    <button><a href="homePageProdutos.php">Voltar para a Home Page</a></button>

    </body>
</html>

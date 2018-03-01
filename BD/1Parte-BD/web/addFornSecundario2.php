<html>
    <head>
        <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $ean = $_REQUEST['ean'];
    $nome = $_REQUEST['nome'];
    $nif = $_REQUEST['nif'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        $sql = "SELECT nif FROM fornecedor WHERE nif = :nif; ";
        $result = $db->prepare($sql);                         
        $result->execute([':nif' => $nif]);
        $temp=$result->fetchAll();

        if(!$temp)
        {
            $sql = "INSERT INTO fornecedor VALUES (:nif, :nome); ";
            $result = $db->prepare($sql);                         
            $result->execute([':nif' => $nif, ':nome' => $nome]);
        }
        
        $sql = "INSERT INTO fornece_sec VALUES (:nif, :ean); ";
        $result = $db->prepare($sql);                         
        $result->execute([':nif' => $nif, ':ean' => $ean]);    

        echo("<p>Fornecedor secundário adicionado.</p>");  

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

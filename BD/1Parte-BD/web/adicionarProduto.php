<html>
     <head>
        <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $ean = $_REQUEST['ean'];
    $design = $_REQUEST['design'];
    $categoria = $_REQUEST['categoria'];
    $nome = $_REQUEST['nome'];
    $forn_primario = $_REQUEST['forn_primario'];
    $today = time();
    $cdate = date("Y-m-d", $today);
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        $sql = "SELECT nif FROM fornecedor WHERE nif = :forn_primario; ";
        $result = $db->prepare($sql);
        $result->execute([':forn_primario' => $forn_primario]);
        $temp=$result->fetchAll();

        if(!$temp)
        {
            $sql = "INSERT INTO fornecedor VALUES (:forn_primario, :nome); ";
            $result = $db->prepare($sql);
            $result->execute([':forn_primario' => $forn_primario, ':nome' => $nome]);
        }

        $sql = "INSERT INTO produto VALUES (:ean, :design, :categoria, :forn_primario, :cdate); ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean, ':design' => $design, ':categoria' => $categoria, ':forn_primario' => $forn_primario, ':cdate' => $cdate]);

        echo("<p>$design adicionado.</p>");  

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
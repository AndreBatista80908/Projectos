<html>
     <head>
        <meta charset="UTF-8">
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
<?php
    $ean = $_REQUEST['ean'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        $db->query("start transaction;");

        $sql = "DELETE FROM reposicao WHERE ean = :ean; ";     /* Necessario devido a foreign key mas sem logica no  */
        $result = $db->prepare($sql);                          /* contexto real porque o produto pode ser removido e */
        $result->execute([':ean' => $ean]);                    /* o registo da reposicao continuar na Base de Dados. */
        
        $sql = "DELETE FROM planograma WHERE ean = :ean; ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean]); 
        
        $sql = "DELETE FROM fornece_sec WHERE ean = :ean; ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean]); 

        $sql = "SELECT forn_primario FROM produto WHERE ean = :ean; ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean]);
        $temp = $result->fetch();
        $nif = $temp[0];
        
        $sql = "SELECT count(forn_primario) FROM produto GROUP BY forn_primario HAVING forn_primario = :nif; ";
        $result = $db->prepare($sql);
        $result->execute([':nif' => $nif]);
        $contador = $result->fetch();

        $sql = "DELETE FROM produto WHERE ean = :ean; ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean]);

        if($contador[0] == 1)
        {
            $sql = "DELETE FROM fornecedor WHERE nif = :nif; ";
            $result = $db->prepare($sql);
            $result->execute([':nif' => $nif]);
        }

        echo("<p>Produto $ean removido.</p>");

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
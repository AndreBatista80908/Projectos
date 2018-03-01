<html>
    <head>
        <meta charset="UTF-8">
        <style>

        table {
            border-collapse: collapse;
        }
        table, td, th {
            border: 1px solid white;
        }
        
        </style>
    </head>
    <link rel="stylesheet" type="text/css" href="mystyle.css">
    <body style="table, th, td : border: 1px solid white;}">

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
    
        $sql = "SELECT operador, instante, unidades FROM reposicao NATURAL JOIN evento_reposicao WHERE ean = :ean; ";
        $result = $db->prepare($sql);
        $result->execute([':ean' => $ean]);

        echo("<h3>Evento de Reposição do Produto $ean</h3>\n");

        echo("<table cellspacing=\"7\">\n");
        echo("<td>Operador</td><td>Instante</td><td>Unidades</td>\n");
        foreach($result as $row)
        {
            echo("<tr>\n");
            echo("<td>{$row['operador']}</td>\n");
            echo("<td>{$row['instante']}</td>\n");
            echo("<td>{$row['unidades']}</td>\n");
            echo("</tr>\n");
        }
        echo("</table>\n");

        $db->query("commit;");

        $db = null;
    }
    catch (PDOException $e)
    {
        $db->query("rollback;");
        echo("<p>ERROR: {$e->getMessage()}</p>");
    }
?>
    <br>
    <button><a href="homePageProdutos.php">Voltar para a Home Page</a></button>

    </body>
</html>
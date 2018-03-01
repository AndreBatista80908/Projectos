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
    <body>

<?php
    $nome = $_REQUEST['nome'];
    $next = $_REQUEST['next'];
    try
    {
        $host = "db.ist.utl.pt";
        $user ="ist180908";
        $password = "fbqs8304";
        $dbname = $user;
        
        $db = new PDO("pgsql:host=$host;dbname=$dbname", $user, $password);
        $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

        if (isset($next))
        {
            $nome = $next;
        }

        $sql = "SELECT nome FROM categoria_simples WHERE nome = :nome;";
        $result = $db->prepare($sql); 
        $result->execute([':nome' => $nome]);
        $temp1 = $result->fetchAll();

        if ($temp1)
        {
            echo("Não existem mais sub-categorias\n");
            echo("<br>");
            echo("<button><a href=\"homePageCategorias.php\">Voltar para a Home Page</a></button>");
        }
        else
        {
            $sql = "SELECT * FROM constituida WHERE super_categoria = :nome;";
            $result = $db->prepare($sql); 
            $result->execute([':nome' => $nome]);
            $temp2 = $result->fetchAll();

            echo("<table border=\"0\" cellspacing=\"5\">\n");
            foreach($temp2 as $row)
            {
                echo("<tr>\n");
                echo("<td>{$row['super_categoria']}</td>\n");
                echo("<td>{$row['categoria']}</td>\n");
                echo("</tr>\n");
            }
            echo("</table>\n");
        }

        if (!$temp1)
        {
            echo("<br>");
            echo("<button><a href=\"listarSubCategorias.php?next={$row['categoria']}\">Descer mais um nível de categorias</a></button>\n");
        }

        $db = null;
    
    }
    catch (PDOException $e)
    {
        echo("<p>ERROR: {$e->getMessage()}</p>");
    }
?>
        
    </body>
</html>
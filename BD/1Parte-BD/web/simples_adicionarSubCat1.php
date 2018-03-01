<html>
	<head>
      <meta charset="UTF-8">
    </head>
	<link rel="stylesheet" type="text/css" href="mystyle.css">
    <body>
    	<h3>Adicionar Sub-Categoria:</h3>
        <form action="simples_adicionarSubCat2.php" method="post">
        	<p><input type="hidden" name="nome" value="<?=$_REQUEST['nome']?>" /></p>
            <p>Nome da sua Sub-Categoria: <input type="text" name="nomeSubCat"/> <input type="submit" value="Adicionar"/></p>
            
        </form>
        <button><a href="homePageCategorias.php">Voltar para a Home Page</a></button>
    </body>
</html>
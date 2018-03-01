-- Populate

-- Categoria
insert into categoria values ('Carnes');
insert into categoria values ('Frutas e Legumes');
insert into categoria values ('Mercearia');
insert into categoria values ('Talho');
insert into categoria values ('Peixaria');
insert into categoria values ('Higiene e Beleza');
insert into categoria values ('Congelados');
insert into categoria values ('Charcutaria');
insert into categoria values ('Padaria');
insert into categoria values ('Laticínios');
insert into categoria values ('Bebidas');
insert into categoria values ('Verduras');
insert into categoria values ('Enlatados');
insert into categoria values ('Limpeza de Pele');
insert into categoria values ('Peixe Fresco');
insert into categoria values ('Peixe Congelado');
insert into categoria values ('Frutas Frescas');
insert into categoria values ('Nectares');
insert into categoria values ('Oleos e Azeites');
insert into categoria values ('Pao de Cereais');
insert into categoria values ('Iogurtes');
insert into categoria values ('Carnes Brancas');
insert into categoria values ('Carnes Vermelhas');
insert into categoria values ('Queijos');
insert into categoria values ('Queijos Franceses');

-- Categoria Simples
insert into categoria_simples values ('Verduras');
insert into categoria_simples values ('Enlatados');
insert into categoria_simples values ('Limpeza de Pele');
insert into categoria_simples values ('Peixe Fresco');
insert into categoria_simples values ('Peixe Congelado');
insert into categoria_simples values ('Frutas Frescas');
insert into categoria_simples values ('Nectares');
insert into categoria_simples values ('Oleos e Azeites');
insert into categoria_simples values ('Pao de Cereais');
insert into categoria_simples values ('Iogurtes');
insert into categoria_simples values ('Carnes Brancas');
insert into categoria_simples values ('Carnes Vermelhas');
insert into categoria_simples values ('Queijos Franceses');

-- Super Categoria
insert into super_categoria values ('Carnes');
insert into super_categoria values ('Frutas e Legumes');
insert into super_categoria values ('Mercearia');
insert into super_categoria values ('Talho');
insert into super_categoria values ('Peixaria');
insert into super_categoria values ('Higiene e Beleza');
insert into super_categoria values ('Congelados');
insert into super_categoria values ('Charcutaria');
insert into super_categoria values ('Padaria');
insert into super_categoria values ('Laticínios');
insert into super_categoria values ('Bebidas');
insert into super_categoria values ('Queijos');

-- Constituida
insert into constituida values ('Frutas e Legumes', 'Verduras');
insert into constituida values ('Mercearia', 		'Enlatados');
insert into constituida values ('Peixaria', 		'Peixe Fresco');
insert into constituida values ('Higiene e Beleza', 'Limpeza de Pele');
insert into constituida values ('Congelados', 		'Peixe Congelado');
insert into constituida values ('Padaria', 			'Pao de Cereais');
insert into constituida values ('Laticínios', 		'Iogurtes');
insert into constituida values ('Bebidas', 			'Nectares');
insert into constituida values ('Talho', 			'Carnes');
insert into constituida values ('Carnes', 			'Carnes Brancas');
insert into constituida values ('Carnes', 			'Carnes Vermelhas');

insert into constituida values ('Charcutaria', 		'Queijos');
insert into constituida values ('Queijos', 			'Queijos Franceses');

-- Fornecedor
insert into fornecedor values ('142536748', 'Begal');
insert into fornecedor values ('142536741', 'Nova Classe');
insert into fornecedor values ('362514965', 'Lusobatata');
insert into fornecedor values ('159753682', 'Longo - Indústrias de Carne');
insert into fornecedor values ('798563201', 'Fernando Leite & Companhia');
insert into fornecedor values ('124578963', 'Palitos Campeoes Lda');
insert into fornecedor values ('789520136', 'Pires Salvaterra Lda');
insert into fornecedor values ('157369852', 'Hiperfrio Lda');
insert into fornecedor values ('429347921', 'Azeitonas & Cia');
insert into fornecedor values ('125793025', 'Nestle');
insert into fornecedor values ('756248632', 'Pakito Lda');
insert into fornecedor values ('739124030', 'Pereira e Santos, S.A');
insert into fornecedor values ('784623800', 'Costa & Martins, Lda');
insert into fornecedor values ('221369571', 'Baptista & Baptista, Lda');
insert into fornecedor values ('791360225', 'Gomes & Valle, Lda');
insert into fornecedor values ('125793026', 'Silva e Silva, Lda');
insert into fornecedor values ('125793027', 'Pereira-Leite, Lda');

insert into fornecedor values ('999999999', 'BBB Bom, Bonito & Barato');

-- Produto
insert into produto values ('1425630255816', 'Arroz', 						'Mercearia', 			'784623800', '2013-02-01');
insert into produto values ('8563255964177', 'Cerejas', 					'Frutas e Legumes', 	'221369571', '2013-12-22');
insert into produto values ('1206532554123', 'Alface', 						'Verduras', 			'221369571', '2013-06-14');
insert into produto values ('1200586322441', 'Azeitonas Pretas', 			'Oleos e Azeites', 		'429347921', '2013-04-27');
insert into produto values ('4515815155517', 'Sumo de Banana e Laranja', 	'Nectares', 			'756248632', '2001-11-17');
insert into produto values ('1256451612933', 'Tampoes', 					'Higiene e Beleza', 	'791360225', '2009-09-24');
insert into produto values ('1252818266000', 'Postas de Pescada', 			'Peixe Congelado', 		'157369852', '1998-01-11');
insert into produto values ('1252524222888', 'Bifes de Frango', 			'Carnes Brancas', 		'159753682', '1996-07-17');
insert into produto values ('8952417632525', 'Robalo', 						'Peixe Fresco', 		'789520136', '2002-10-25');
insert into produto values ('4125362418926', 'Atum em lata', 				'Enlatados', 			'739124030', '2006-03-30');
insert into produto values ('1020504259263', 'Cenoura', 					'Frutas e Legumes', 	'221369571', '2003-03-15');
insert into produto values ('1289658525945', 'Azeite', 						'Mercearia', 			'784623800', '2013-04-19');
insert into produto values ('2352718549596', 'Cereais Nesquik', 			'Mercearia', 			'125793025', '2004-12-25');
insert into produto values ('1200135641666', 'Fiambre da Perna Extra', 		'Charcutaria', 			'159753682', '2005-11-23');
insert into produto values ('2526242829999', 'Cafe Soluvel', 				'Mercearia', 			'784623800', '2012-07-02');
insert into produto values ('2019875623256', 'Palitos', 					'Mercearia', 			'124578963', '2005-04-12');
insert into produto values ('2252855232663', 'Batata Branca', 				'Frutas e Legumes', 	'362514965', '2008-06-12');
insert into produto values ('8242912635111', 'Maça', 						'Frutas e Legumes', 	'221369571', '2008-02-05');
insert into produto values ('7184158415845', 'Queijo de Cabra', 			'Queijos', 				'798563201', '2000-03-30');
insert into produto values ('8485784156789', 'Desmaquilhante Nivea', 		'Higiene e Beleza', 	'791360225', '2006-06-05');

insert into produto values ('1206532554199', 'Couve', 						'Verduras', 			'999999999', '2013-06-15');
insert into produto values ('4125362418999', 'Sardinhas em lata', 			'Enlatados', 			'999999999', '2006-03-31');
insert into produto values ('1256451612999', 'Creme Nivea', 				'Limpeza de Pele', 		'999999999', '2009-09-25');
insert into produto values ('8952417632599', 'Dourada', 					'Peixe Fresco', 		'999999999', '2002-10-26');
insert into produto values ('1252818266099', 'Postas de Bacalhau', 			'Peixe Congelado', 		'999999999', '1998-01-12');
insert into produto values ('1020504259299', 'Abacaxi', 					'Frutas Frescas', 		'999999999', '2003-03-16');
insert into produto values ('4515815155599', 'Sumo de Manga', 				'Nectares', 			'999999999', '2001-11-18');
insert into produto values ('1200586322499', 'Oleo de Girassol', 			'Oleos e Azeites', 		'999999999', '2013-04-28');
insert into produto values ('1425630255899', 'Pao com sementes', 			'Pao de Cereais', 		'999999999', '2013-02-02');
insert into produto values ('7184158415899', 'Queijo de Vaca', 				'Queijos', 				'999999999', '2009-03-31');
insert into produto values ('7184158415999', 'Iogurte de Banana', 			'Iogurtes', 			'999999999', '2000-03-31');
insert into produto values ('1252524222899', 'Bifes de Peru', 				'Carnes Brancas', 		'999999999', '1995-07-18');
insert into produto values ('1252524222999', 'Bifes de Porco', 				'Carnes Vermelhas', 	'999999999', '1996-07-18');

-- Fornecedor Secundario
insert into fornece_sec values ('739124030', '1425630255816');
insert into fornece_sec values ('791360225', '1206532554123');
insert into fornece_sec values ('362514965', '1020504259263');
insert into fornece_sec values ('784623800', '4125362418926');
insert into fornece_sec values ('798563201', '1200135641666');
insert into fornece_sec values ('124578963', '2526242829999');
insert into fornece_sec values ('789520136', '2352718549596');
insert into fornece_sec values ('157369852', '8952417632525');
insert into fornece_sec values ('429347921', '1289658525945');
insert into fornece_sec values ('125793026', '8563255964177');
insert into fornece_sec values ('125793027', '1200586322441');
insert into fornece_sec values ('125793025', '2019875623256');

insert into fornece_sec values ('739124030', '2019875623256');
insert into fornece_sec values ('791360225', '2019875623256');
insert into fornece_sec values ('362514965', '2019875623256');
insert into fornece_sec values ('784623800', '2019875623256');
insert into fornece_sec values ('798563201', '2019875623256');
insert into fornece_sec values ('124578963', '2019875623256');
insert into fornece_sec values ('789520136', '2019875623256');
insert into fornece_sec values ('157369852', '2019875623256');
insert into fornece_sec values ('429347921', '2019875623256');
insert into fornece_sec values ('125793026', '2019875623256');

-- Corredor
insert into corredor values ('1',  '5');
insert into corredor values ('2',  '5');
insert into corredor values ('3',  '5');
insert into corredor values ('4',  '5');
insert into corredor values ('5',  '6');
insert into corredor values ('6',  '6');
insert into corredor values ('7',  '6');
insert into corredor values ('8',  '6');
insert into corredor values ('9',  '4');
insert into corredor values ('10', '4');

-- Prateleira
insert into prateleira values ('1', 'esquerdo', 'chao');
insert into prateleira values ('1', 'esquerdo', 'medio');
insert into prateleira values ('1', 'esquerdo', 'superior');
insert into prateleira values ('1', 'direito', 	'chao');
insert into prateleira values ('1', 'direito', 	'medio');
insert into prateleira values ('1', 'direito', 	'superior');
insert into prateleira values ('2', 'esquerdo', 'chao');
insert into prateleira values ('2', 'esquerdo', 'medio');
insert into prateleira values ('2', 'esquerdo', 'superior');
insert into prateleira values ('2', 'direito', 	'chao');
insert into prateleira values ('2', 'direito', 	'medio');
insert into prateleira values ('2', 'direito', 	'superior');
insert into prateleira values ('3', 'esquerdo', 'chao');
insert into prateleira values ('3', 'esquerdo', 'medio');
insert into prateleira values ('3', 'esquerdo', 'superior');
insert into prateleira values ('3', 'direito', 	'chao');
insert into prateleira values ('3', 'direito', 	'medio');
insert into prateleira values ('3', 'direito', 	'superior');
insert into prateleira values ('4', 'esquerdo', 'chao');
insert into prateleira values ('4', 'esquerdo', 'medio');
insert into prateleira values ('4', 'esquerdo', 'superior');
insert into prateleira values ('4', 'direito', 	'chao');
insert into prateleira values ('4', 'direito', 	'medio');
insert into prateleira values ('4', 'direito', 	'superior');
insert into prateleira values ('5', 'esquerdo', 'chao');
insert into prateleira values ('5', 'esquerdo', 'medio');
insert into prateleira values ('5', 'esquerdo', 'superior');
insert into prateleira values ('5', 'direito', 	'chao');
insert into prateleira values ('5', 'direito', 	'medio');
insert into prateleira values ('5', 'direito', 	'superior');

-- Planograma
insert into planograma values ('1425630255816', '1',  'esquerdo', 	'chao', 	'5',  '30', '1');
insert into planograma values ('8563255964177', '2',  'direito', 	'medio', 	'10', '10', '2');
insert into planograma values ('1206532554123', '2',  'esquerdo', 	'superior', '20', '20', '3');
insert into planograma values ('1200586322441', '4',  'direito', 	'medio', 	'2',  '5',  '4');
insert into planograma values ('4515815155517', '4',  'direito', 	'chao', 	'2',  '30', '5');
insert into planograma values ('1256451612933', '4',  'esquerdo', 	'medio', 	'2',  '22', '6');
insert into planograma values ('1252818266000', '4',  'esquerdo', 	'superior', '1',  '7',  '7');
insert into planograma values ('1252524222888', '5',  'direito', 	'superior', '5',  '10', '8');
insert into planograma values ('8952417632525', '5',  'direito', 	'chao', 	'2',  '10', '9');
insert into planograma values ('4125362418926', '5',  'esquerdo', 	'superior', '3',  '60', '10');
insert into planograma values ('1020504259263', '5',  'esquerdo', 	'chao', 	'20', '20', '11');
insert into planograma values ('1289658525945', '2',  'direito', 	'superior', '4',  '30', '12');
insert into planograma values ('2352718549596', '2',  'esquerdo', 	'superior', '1',  '15', '13');
insert into planograma values ('1200135641666', '3',  'esquerdo', 	'medio', 	'1',  '17', '14');
insert into planograma values ('2526242829999', '1',  'esquerdo', 	'superior', '4',  '25', '15');
insert into planograma values ('2019875623256', '1',  'direito', 	'medio', 	'1',  '10', '16');
insert into planograma values ('2252855232663', '1',  'direito', 	'chao', 	'5',  '5',  '17');
insert into planograma values ('8242912635111', '3',  'direito', 	'superior', '5',  '10', '18');
insert into planograma values ('7184158415845', '3',  'direito', 	'medio', 	'2',  '5',  '19');
insert into planograma values ('8485784156789', '3',  'esquerdo', 	'chao', 	'1',  '12', '20');

-- Evento Reposiçao
insert into evento_reposicao values ('241088861','2017-09-20');
insert into evento_reposicao values ('241088861','2017-11-22');
insert into evento_reposicao values ('241088861','2017-07-24');
insert into evento_reposicao values ('247778861','2017-02-25');
insert into evento_reposicao values ('241001161','2017-04-21');
insert into evento_reposicao values ('247778861','2017-06-20');
insert into evento_reposicao values ('247778861','2017-08-29');
insert into evento_reposicao values ('241088861','2017-02-01');
insert into evento_reposicao values ('241001161','2017-04-14');
insert into evento_reposicao values ('241001161','2017-03-13');
insert into evento_reposicao values ('247778861','2017-11-18');
insert into evento_reposicao values ('241088861','2017-10-03');
insert into evento_reposicao values ('247778861','2017-11-07');
insert into evento_reposicao values ('241001161','2017-11-08');
insert into evento_reposicao values ('247778861','2017-07-04');
insert into evento_reposicao values ('241001161','2017-02-19');
insert into evento_reposicao values ('241088861','2017-03-05');
insert into evento_reposicao values ('241001161','2017-05-11');
insert into evento_reposicao values ('241001161','2017-02-14');
insert into evento_reposicao values ('247778861','2017-03-02');

insert into evento_reposicao values ('222229999','2017-09-21');
insert into evento_reposicao values ('222229999','2017-11-23');
insert into evento_reposicao values ('222229999','2017-07-25');
insert into evento_reposicao values ('222229999','2017-02-26');
insert into evento_reposicao values ('222229999','2017-04-22');
insert into evento_reposicao values ('222229999','2017-06-21');
insert into evento_reposicao values ('222229999','2017-08-30');
insert into evento_reposicao values ('222229999','2017-02-02');
insert into evento_reposicao values ('222229999','2017-04-15');
insert into evento_reposicao values ('222229999','2017-03-14');
insert into evento_reposicao values ('222229999','2017-11-19');
insert into evento_reposicao values ('222229999','2017-10-04');
insert into evento_reposicao values ('222229999','2017-11-08');
insert into evento_reposicao values ('222229999','2017-11-09');
insert into evento_reposicao values ('222229999','2017-07-05');
insert into evento_reposicao values ('222229999','2017-02-20');
insert into evento_reposicao values ('222229999','2017-03-06');
insert into evento_reposicao values ('241088861','2017-05-12');
insert into evento_reposicao values ('247778861','2017-02-15');
insert into evento_reposicao values ('241001161','2017-03-03');

-- Reposiçao
insert into reposicao values ('1425630255816', '1',  'esquerdo', 	'chao', 	'241088861',  '2017-09-20', '28');
insert into reposicao values ('8563255964177', '2',  'direito', 	'medio', 	'247778861',  '2017-02-25', '8');
insert into reposicao values ('1206532554123', '2',  'esquerdo', 	'superior', '247778861',  '2017-06-20', '18');
insert into reposicao values ('1200586322441', '4',  'direito', 	'medio', 	'241088861',  '2017-11-22', '3');
insert into reposicao values ('4515815155517', '4',  'direito', 	'chao', 	'241001161',  '2017-04-21', '28');
insert into reposicao values ('1256451612933', '4',  'esquerdo', 	'medio', 	'241088861',  '2017-07-24', '20');
insert into reposicao values ('1252818266000', '4',  'esquerdo', 	'superior', '241001161',  '2017-04-14', '5');
insert into reposicao values ('1252524222888', '5',  'direito', 	'superior', '241088861',  '2017-02-01', '8');
insert into reposicao values ('8952417632525', '5',  'direito', 	'chao', 	'247778861',  '2017-08-29', '8');
insert into reposicao values ('4125362418926', '5',  'esquerdo', 	'superior', '241001161',  '2017-03-13', '49');
insert into reposicao values ('1020504259263', '5',  'esquerdo', 	'chao', 	'241088861',  '2017-10-03', '9');
insert into reposicao values ('1289658525945', '2',  'direito', 	'superior', '241001161',  '2017-11-08', '19');
insert into reposicao values ('2352718549596', '2',  'esquerdo', 	'superior', '241001161',  '2017-02-19', '14');
insert into reposicao values ('1200135641666', '3',  'esquerdo', 	'medio', 	'247778861',  '2017-11-18', '16');
insert into reposicao values ('2526242829999', '1',  'esquerdo', 	'superior', '247778861',  '2017-11-07', '24');
insert into reposicao values ('2019875623256', '1',  'direito', 	'medio', 	'241001161',  '2017-05-11', '9');
insert into reposicao values ('2252855232663', '1',  'direito', 	'chao', 	'247778861',  '2017-07-04', '1');
insert into reposicao values ('8242912635111', '3',  'direito', 	'superior', '241088861',  '2017-03-05', '4');
insert into reposicao values ('7184158415845', '3',  'direito', 	'medio', 	'247778861',  '2017-03-02', '1');
insert into reposicao values ('8485784156789', '3',  'esquerdo', 	'chao', 	'241001161',  '2017-02-14', '9');

insert into reposicao values ('1425630255816', '1',  'esquerdo', 	'chao', 	'222229999',  '2017-09-21', '1');
insert into reposicao values ('8563255964177', '2',  'direito', 	'medio', 	'222229999',  '2017-11-23', '1');
insert into reposicao values ('1206532554123', '2',  'esquerdo', 	'superior', '222229999',  '2017-07-25', '1');
insert into reposicao values ('1200586322441', '4',  'direito', 	'medio', 	'222229999',  '2017-02-26', '1');
insert into reposicao values ('4515815155517', '4',  'direito', 	'chao', 	'222229999',  '2017-04-22', '1');
insert into reposicao values ('1256451612933', '4',  'esquerdo', 	'medio', 	'222229999',  '2017-06-21', '1');
insert into reposicao values ('1252818266000', '4',  'esquerdo', 	'superior', '222229999',  '2017-08-30', '1');
insert into reposicao values ('1252524222888', '5',  'direito', 	'superior', '222229999',  '2017-02-02', '1');
insert into reposicao values ('8952417632525', '5',  'direito', 	'chao', 	'222229999',  '2017-04-15', '1');
insert into reposicao values ('4125362418926', '5',  'esquerdo', 	'superior', '222229999',  '2017-03-14', '1');
insert into reposicao values ('1020504259263', '5',  'esquerdo', 	'chao', 	'222229999',  '2017-11-19', '1');
insert into reposicao values ('1289658525945', '2',  'direito', 	'superior', '222229999',  '2017-10-04', '1');
insert into reposicao values ('2352718549596', '2',  'esquerdo', 	'superior', '222229999',  '2017-11-08', '1');
insert into reposicao values ('1200135641666', '3',  'esquerdo', 	'medio', 	'222229999',  '2017-11-09', '1');
insert into reposicao values ('2526242829999', '1',  'esquerdo', 	'superior', '222229999',  '2017-07-05', '1');
insert into reposicao values ('2019875623256', '1',  'direito', 	'medio', 	'222229999',  '2017-02-20', '1');
insert into reposicao values ('2252855232663', '1',  'direito', 	'chao', 	'222229999',  '2017-03-06', '1');
insert into reposicao values ('8242912635111', '3',  'direito', 	'superior', '241088861',  '2017-05-12', '1');
insert into reposicao values ('7184158415845', '3',  'direito', 	'medio', 	'247778861',  '2017-02-15', '1');
insert into reposicao values ('8485784156789', '3',  'esquerdo', 	'chao', 	'241001161',  '2017-03-03', '1');
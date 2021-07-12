<!-- For rendering markdown LaTeX into pdf -->
<script type="text/javascript" src="http://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
<script type="text/x-mathjax-config">
		MathJax.Hub.Config({ tex2jax: {inlineMath: [['$', '$']]}, messageStyle: "none" });
</script>

<center>
	<img src="assets/uslogo.png">
  <h2> Universidade Estadual do Ceará &ndash; UECE </h2>
</center>

<p>

  **Curso:** Ciência da Computação<br>
  **Disciplina:** Projeto e Análise de Algoritmos<br>
  **Docente:** Leonardo Sampaio Rocha<br>
  **Discente:** Gabriel Furtado Lins Melo<br>
  **Matrícula:** 1394225<br>

</p>

<hr>

<center>
  <h2> Problema do Corte de Tecido </h2>
</center>

<h3>Índice</h3>

- [Descrição do problema](#descrição-do-problema)
- [Explicação do código](#explicação-do-código)
	- [Entrada](#entrada)
	- [Instância do problema](#instância-do-problema)
	- [Resolução](#resolução)
- [Análise da complexidade](#análise-da-complexidade)
- [Como executar (Windows)](#como-executar-windows)
- [Como executar (Linux)](#como-executar-linux)

<hr>

### Descrição do problema

<p>

A entrada é uma peça de tecido de dimensões X × Y, onde X e Y são inteiros positivos, e uma lista de n peças retangulares que podem ser feitas a partir do tecido. Cada peça i $\in$ [1 ... n] é formada por um retângulo de dimensões a<sub>i</sub> por b<sub>i</sub>, e possui preço de venda p<sub>i</sub>, sendo estas informações dadas na entrada, onde a<sub>i</sub>, b<sub>i</sub> e p<sub>i</sub> são sempre inteiros positivos. Você possui uma máquina capaz de cortar um tecido em duas peças, horizontalmente ou verticalmente e deve projetar e implementar um algoritmo que determine a melhor receita possível sobre o tecido de dimensão X × Y, fornecendo também uma análise da complexidade do algoritmo. Em uma solução, é possível ter várias cópias de uma peça.

</p>


### Explicação do código

#### Entrada

<p>

A entrada para a instância do *solver* implementado consiste, nesta ordem, de:

- Um inteiro *n*, indicando a quantidade de entradas (possíveis cortes) serão dadas (seria possível uma implementação que obtesse toda a entrada e calculasse, apenas posteriormente, o n. No entanto, uma vez que a linguagem escolhida foi C++, visando uma melhor performance, a complexidade da implementação de tal mecanismo o torna inviável);
- As dimensões *x* e *y* do tecido original;
- O vetor de tamanhos de cortes *a*;
- O vetor de tamanhos de cortes *b*;
- O vetor dos preços *p* de cada corte *a*<sub>i</sub> x *b*<sub>i</sub>;

A seção do código que recebe a entrada permite que a mesma seja inserida com o input padrão *cin* através do teclado, ou passada por um arquivo através do operador `<`. Exemplo:

```
$ ./main < entrada.txt
```

Abaixo é possível visualizar o trecho do código que implementa a leitura da entrada.

```
Fabric readInput()
{
	Fabric fabricInstance;
	fabricInstance.n = 0;

	std::cin >> fabricInstance.n;
	std::cin >> fabricInstance.x >> fabricInstance.y;

	fabricInstance.cuts.resize(fabricInstance.n);

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].a;
	}

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].b;
	}

	for (int i = 0; i < fabricInstance.n; i++)
	{
		std::cin >> fabricInstance.cuts[i].p;
	}

	return fabricInstance;
}
```

</p>

#### Instância do problema

<p>

Uma instância do problema foi definida como uma estrutura capaz de portar todas as variáveis mencionadas na [entrada](#entrada) e a solução do problema, conforme o trecho de código abaixo.

```
struct Fabric
{
	int n, x, y;
	std::vector<Cut> cuts;
	std::vector<int> frequencies;
	int bestValue;
	bool solved = false;
};
```

</p>

#### Resolução

<p>

Ao passar a instância inicializada do problema para o *solver*, este calcula, utilizando programação dinâmica, a melhor solução (maior preço) e as frequências de cada corte de tecido utilizado. A seguir, será explicado o funcionamento cada trecho do código.

Inicializamos duas matrizes de programação dinâmica, de tamanho *MAXVAL* x *MAXVAL*, este setado alto o suficiente para conter o maior valor de dimensão dentre os vetores a e b, de forma a, durante a execução, considerar todos os possíveis valores. As matrizes *cutsPrices* e *cutsFrequencies* representam, respectivamente, o melhor preço e um vetor de frequências para o índice de cada corte, de forma a armazenar os preços e frequências de todas as combinações possíveis que cabem dentro do tecido.

```
int cutsPrices[MAXVAL][MAXVAL] = {0};
std::multiset<int> cutsFrequencies[MAXVAL][MAXVAL];

for (int i = 0; i < instance->n; i++)
{
	cutsPrices[instance->cuts[i].a][instance->cuts[i].b] = instance->cuts[i].p;
	cutsPrices[instance->cuts[i].b][instance->cuts[i].a] = instance->cuts[i].p;
	cutsFrequencies[instance->cuts[i].a][instance->cuts[i].b] = std::multiset<int>{i};
	cutsFrequencies[instance->cuts[i].b][instance->cuts[i].a] = std::multiset<int>{i};
}
```

Agora veremos o algoritmo que, de fato, implementa a busca pelo valor ótimo. Para iniciar, devemos iterar as matrizes em todos os possíveis valores com i de 0 até *x*, e j de 0 até *y*, de forma a calcular dinamicamente, para cada elemento `matriz[i][j]`, o melhor valor e as frequências baseando-se nos previamente calculados.

Para respeitar a restrição de não cortar mais tecido do que possuímos, o cálculo de cada valor `matriz[i][j]` é feito percorrendo-se *i*, ou *j*, com um iterador *k* apenas até a metade, e somando os preços calculados de `matriz[k][j]` com `matriz[i - k][j]`, por exemplo. Desta forma, a soma das dimensões jamais passarão dos valores dados, bem como sabemos que todos os valores serão considerados, observada a simetria da matriz de programação dinâmica neste caso. Na soma das matrizes `matriz[k][j]` com `matriz[i - k][j]`, verificamos se o valor resultante é maior do que o previamente calculado para o preço de `matriz[i][j]` e, em caso afirmativo, armazenamos aquele melhor valor de `matriz[i][j]` e reiniciamos os valores de frequências armazenados para recalculá-los com base nos novos índices encontrados. Ao final da execução, teremos na matriz `cutsPrices[x][y]` os valores ótimos calculados e na `cutsFrequencies[x][y]` um multiconjunto (estrutura do C++ correspondente a um conjunto que permite a repetição de valores e, automaticamente, realiza operações ordenadas em seus valores, como a inserção, por exemplo) contendo os índices inseridos repetidamente para cada vez que um dos cortes foi utilizado.

```
for (int i = 0; i <= instance->x; i++)
{
	for (int j = 0; j <= instance->y; j++)
	{
		std::multiset<int> localIdxFreq;
		int localBestVal = 0;

		for (int k = 0; k <= i / 2; k++)
		{
			if (localBestVal < cutsPrices[k][j] + cutsPrices[i - k][j])
			{
				localBestVal = cutsPrices[k][j] + cutsPrices[i - k][j];

				localIdxFreq.clear();

				for (auto w : cutsFrequencies[k][j])
					localIdxFreq.insert(w);

				for (auto w : cutsFrequencies[i - k][j])
					localIdxFreq.insert(w);
			}
		}

		for (int k = 0; k <= j / 2; k++)
		{
			if (localBestVal < cutsPrices[i][k] + cutsPrices[i][j - k])
			{
				localBestVal = cutsPrices[i][k] + cutsPrices[i][j - k];

				localIdxFreq.clear();

				for (auto w : cutsFrequencies[i][k])
					localIdxFreq.insert(w);

				for (auto w : cutsFrequencies[i][j - k])
					localIdxFreq.insert(w);
			}
		}

		cutsPrices[i][j] = localBestVal;
		cutsFrequencies[i][j] = localIdxFreq;
	}
}
```

</p>

### Análise da complexidade

<p>

Considerando as duas iterações aninhadas de i para x e j para y, já teríamos uma complexidade temporal de O(xy). No entanto, para cada execução deste *for* aninhado, fazemos mais dois laços, um percorrendo i até sua metade, e outro, da mesma forma, para j. O caso de maior complexidade destes laços internos seria de x / 2 e y / 2, mas isto só ocorre 1 vez durante a execução. Levando à risca o número de execuções dos laços mais internos e utilizando a fórmula 

<center>

$$
\sum_{i=0}^{n}i = \frac{n (n + 1)}{2}
$$

</center>

temos que a soma da quantidade de iterações dos laços mais internos, multiplicada pelas iterações externas xy, leva a: $\frac{x^3y + y^3x + 2(x^2y+y^2x)}{8}$ iterações.

</p>

### Como executar (Windows)

<p>

Num terminal (prompt de comando), navegue até o diretório do projeto "*FabricCutting*", dê o comando para compilar todos os códigos-fonte no diretório *src* e utilizar os *headers* do diretório *include*, gerando um executável *main*:

```
> g++ src\*.cpp -Iinclude -o main.exe
```

Agora é só executar a main com:

```
> main.exe
```

Se quiser passar a entrada a partir de um arquivo, é só fazer:

```
> main.exe < entrada.txt
```

</p>

### Como executar (Linux)

Dê permissão ao *bash script* "*run.sh*" com:

```
$ chmod +x run.sh
```

E, então, o execute:

```
$ ./run.sh
```

Para compilar e executar por conta própria, basta seguir os comandos do *shell script* como exemplo.

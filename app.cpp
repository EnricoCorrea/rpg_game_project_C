#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAX_VERTICES = 9;
bool bencaoDeuses = false;
bool pocao = false;
int vida;
int vidaInimigo = 0;
bool grimorio = false, cajado = false;
bool espada = false, machado = false;
bool completa1=false, completa2=false, completa3=false, completa4=false, completa5=false, completa6=false, completa7=false, completa8=false;
bool mago = false;
bool guerreiro = false;
int recuperar = 0;

class TabelaHash {
  private:
    static const int MAX = 10;

    struct No {
        string chave;
        int valorvida;
        int valor;
        No* prox;
    };

    No* tabelaHash[MAX];

    int funcaoHash(string chave) {
        return chave.length() % MAX;
    }

  public:
    TabelaHash() {
        for (int i = 0; i < MAX; i++) {
            tabelaHash[i] = NULL;
        }
    }

    void inserir(string chave, int valor) {
        int posicao = funcaoHash(chave);
        No* temp = tabelaHash[posicao];
        No* novo = new No;
        novo->chave = chave;
        novo->valor = valor;
        novo->prox = tabelaHash[posicao];
        tabelaHash[posicao] = novo;
    }

    int buscar(string chave) {
        int posicao = funcaoHash(chave);
        No* temp = tabelaHash[posicao];
        while (temp != NULL) {
            if (temp->chave == chave) {
                return temp->valor;
            }
            temp = temp->prox;
        }
        return 1000;
    }

    void remover(string chave) {
        int posicao = funcaoHash(chave);
        No* temp = tabelaHash[posicao];
        No* ant = NULL;
        while (temp != NULL) {
            if (temp->chave == chave) {
                if (ant == NULL) {
                    tabelaHash[posicao] = temp->prox;
                } else {
                    ant->prox = temp->prox;
                }
                delete temp;
                return;
            }
            ant = temp;
            temp = temp->prox;
        }
    }


    void mostrarTabela() {
        for (int i = 0; i < MAX; i++) {
            cout << i << " --> ";
            No* temp = tabelaHash[i];
            while (temp != NULL) {
                cout << "Inimigo: " << temp->chave << " | Vida: " << temp->valor << " ";
                temp = temp->prox;
            }
            cout << endl;
        }
    }

    void atualizar(string chave, int novoValor) {
    int posicao = funcaoHash(chave);
    No* temp = tabelaHash[posicao];
    while (temp != NULL) {
        if (temp->chave == chave) {
            temp->valor = novoValor;
            return;
        }
        temp = temp->prox;
    }
}
};

class Fila {
  private:
    int vetor[MAX_VERTICES];
    int inicio = -1, fim = -1, tamanho = 0;

  public:
    bool vazia() {
        return tamanho == 0;
    }

    bool cheia() {
        return tamanho == MAX_VERTICES;
    }

    void enfila(int valor) {
        if (!cheia()) {
            fim = (fim + 1) % MAX_VERTICES;
            vetor[fim] = valor;
            tamanho++;
            if (inicio == -1) {
                inicio = 0;
            }
        }
    }

    int desenfila() {
        if (!vazia()) {
            int valor = vetor[inicio];
            inicio = (inicio + 1) % MAX_VERTICES;
            tamanho--;
            return valor;
        }
        return -1;
    }
};

class Pilha {
  private:
    int vetor[MAX_VERTICES];
    int topo = -1;

  public:
    bool vazia() {
        return topo == -1;
    }

    bool cheia() {
        return topo == MAX_VERTICES - 1;
    }

    void push(int valor) {
        if (!cheia()) {
            topo++;
            vetor[topo] = valor;
        }
    }

    int pop() {
        int dado = -1;
        if (!vazia()) {
            dado = vetor[topo];
            topo--;
        }
        return dado;
    }
};
class Grafo {
 private:
    int numVertices;
    int matrizAdj [MAX_VERTICES] [MAX_VERTICES];
    string vertices [MAX_VERTICES];

 public:
    Grafo(int n, string nomes[]) {
        if (n > MAX_VERTICES){
            numVertices = MAX_VERTICES;
        } else {
            numVertices = n;
        }

        for (int i = 0; i < numVertices; i++){
            for (int j = 0; j < numVertices; j++){
                matrizAdj[i][j] = 0;
            }
        }
        for (int i = 0; i < numVertices; i++){
            vertices[i] = nomes[i];
        }
    }
    void adicionarAresta(int v1, int v2, int peso){
        if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices && peso > 0){
            matrizAdj[v1][v2] = peso;
            matrizAdj[v2][v1] = peso;
        }
    }
    void mostrarMatriz() {
        cout << "\nMatriz de Adjac�ncias:" << endl;

        cout << "  ";
        for (int j = 0; j < numVertices; j++){
            cout << vertices[j] << " ";
        }
        cout << endl;

        for (int i = 0; i < numVertices; i++) {
            cout << vertices[i] << " ";
            for (int j = 0; j < numVertices; j++) {
                cout << " " << matrizAdj[i][j] << " ";
            }
            cout << endl;
        }
    }

    void mostraVertices() {
        cout << "\nV�rtices:" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << i << " -> " << vertices[i] << endl;
        }
    }
int pesoAresta(int v1, int v2) {
    if(v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 < numVertices) {
        return matrizAdj [v1][v2];
    }
    return -1;
}

int indiceVertice(string nome) {
    for (int i=0; i < numVertices; i++){
        if(vertices[i] == nome) {
            return i;
        }
    }
    return -1;
}

int grauVertice(int indice) {

    if (indice < 0 || indice >= numVertices) {
        return -1;
    }

    int grau = 0;
    for (int j = 0; j < numVertices; j++) {
        if (matrizAdj[indice][j] > 0) {
            grau++;
        }
    }
    return grau;
}

string* buscaPorNivel(int inicio, int nivelDesejado) {

        bool visitado[MAX_VERTICES] = {false};
        int nivel[MAX_VERTICES];
        for (int i = 0; i < numVertices; i++) {
            nivel[i] = -1;
        }

        Fila fila;
        visitado[inicio] = true;
        nivel[inicio] = 0;
        fila.enfila(inicio);

        while (!fila.vazia()) {
            int v = fila.desenfila();

            for (int i = 0; i < numVertices; i++) {
                if (matrizAdj[v][i] > 0 && !visitado[i]) {
                    visitado[i] = true;
                    nivel[i] = nivel[v] + 1;
                    fila.enfila(i);
                }
            }
        }

        static string retorno[MAX_VERTICES];
        int j = 0;
        bool encontrou = false;
        for (int i = 0; i < numVertices; i++) {
            if (nivel[i] == nivelDesejado) {
                retorno[j] = vertices[i];
                j++;
                encontrou = true;
            }
        }
        retorno[j] = "";
        return retorno;
    }
};

int danoMachado(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 6);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);
    int dado3 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue pena! Voc� errou o ataque!\n";
    } else {
        int critico = distrib2(gen);

        if (critico <= 3 && !bencaoDeuses){
            cout << "\nVoc� acertou o machado num ponto vital! Isso causou dano cr�tico!\n";
            danoTotal = (dado1+dado2+1) * 2;
        } else if (critico <= 3 && bencaoDeuses){
            cout << "\nVoc� acertou o machado num ponto vital! Isso causou dano cr�tico!\n";
            danoTotal = (dado1+dado2+dado3+1) * 2;
        } else if (bencaoDeuses){
            cout << "\nVoc� cortou o inimigo com o machado!\n";
            danoTotal = dado1+dado2+dado3+1;
        } else {
            cout << "\nVoc� cortou o inimigo com o machado!\n";
            danoTotal = dado1+dado2+1;
        }
    }
    return danoTotal;
}

int danoGrimorio(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 8);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);
    int dado3 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue pena! Voc� errou o ataque!\n";
    } else {
        int critico = distrib2(gen);

        if (critico <= 3 && !bencaoDeuses){
            cout << "\nVoc� conjurou uma magia antiga muito poderosa! Isso causou dano cr�tico!\n";
            danoTotal = (dado1+dado2+1) * 2;
        } else if (critico <= 3 && bencaoDeuses){
            cout << "\nVoc� conjurou uma magia antiga muito poderosa! Isso causou dano cr�tico!\n";
            danoTotal = (dado1+dado2+dado3+1) * 2;
        } else if (bencaoDeuses){
             cout << "\nVoc� conjurou uma magia no inimigo!\n";
            danoTotal = dado1+dado2+dado3+1;
        } else {
            cout << "\nVoc� conjurou uma magia no inimigo!\n";
            danoTotal = dado1+dado2+1;
        }
    }
    return danoTotal;
}

int danoEspada(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 8);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);
    int dado3 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue pena! Voc� errou o ataque!\n";
    } else {
        if(!bencaoDeuses){
            cout << "\nVoc� cortou o inimigo com a espada!\n";
            danoTotal = dado1+dado2+2;
        } else {
            cout << "\nVoc� cortou o inimigo com a espada!\n";
            danoTotal = dado1+dado2+dado3+2;
        }
    }
    return danoTotal;
}

int danoCajado(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);
    int dado3 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue pena! Voc� errou o ataque!\n";
    } else {
        if(!bencaoDeuses){
            cout << "\nVoc� conjurou um orbe m�gico no inimigo!\n";
            danoTotal = dado1+dado2+2;
        } else {
            cout << "\nVoc� conjurou um orbe m�gico no inimigo!\n";
            danoTotal = dado1+dado2+dado3+2;
        }
    }
    return danoTotal;
}

//Dano do Goblin 2d3+2
int danoGoblin(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 3);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue sorte! O goblin errou o ataque!\n";
    } else {
        cout << "\nO goblin te acerta com um ataque feroz!\n";
        danoTotal = dado1+dado2+2;
        cout << "Voc� recebe " << danoTotal;
    }
    return danoTotal;
}

//Dano do Esqueleto 2d6+1
int danoEsqueleto(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 4);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue sorte! O esqueleto errou o ataque!\n";
    } else {
        cout << "\nO esqueleto Larry te acerta com um ataque feroz!\n";
        danoTotal = dado1+dado2+1;
        cout << "Voc� recebe " << danoTotal;
    }
    return danoTotal;
}

//Dano do Lobo 2d8+2
int danoLobo(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 8);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue sorte! O lobo errou o ataque!\n";
    } else {
        cout << "\nO lobo te acerta com uma forte mordida! Seus dentes afiados danificam levemente sua armadura.\n";
        danoTotal = dado1+dado2+1;
        cout << "Voc� recebe " << danoTotal;
    }
    return danoTotal;
}

//Dano do Ogro 2d10+2
int danoOgro(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue sorte! O ogro errou o ataque!\n";
    } else {
        cout << "\nO ogro te acerta com uma grande clava! Voc� se sente tonto com tamanha for�a.\n";
        danoTotal = dado1+dado2+2;
        cout << "Voc� recebe " << danoTotal;
    }
    return danoTotal;
}

/* Dano do Drag�o:
Ataque de Asas -> 2d10+4
Ataque de Garras -> 3d10+4
Rajada de Fogo -> 4d10+4
*/
int danoDragao(){
    int danoTotal = 0;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10);


    int dado1 = distrib(gen);
    int dado2 = distrib(gen);
    int dado3 = distrib(gen);
    int dado4 = distrib(gen);

    uniform_int_distribution<> distrib2(1, 10);

    int acerto = distrib2(gen);
    if (acerto == 1){
        cout << "\nQue sorte! O drag�o errou o ataque!\n";
    } else if(acerto<=5){
        cout << "\nO drag�o bate suas asas e lan�a uma forte ventania em voc�! \n A for�a dos ventos faz seu corpo sair do ch�o e ser arremesado nas paredes.\n";
        danoTotal = dado1+dado2+4;
        cout << "Voc� recebe " << danoTotal;
    } else if(acerto<=9){
        cout << "\nO drag�o te acerta com longas garras! \n Voc� sente sua armadura sendo perfurada pela gigantesca criatura.\n";
        danoTotal = dado1+dado2+dado3+4;
        cout << "Voc� recebe " << danoTotal;
    } else {
        cout << "\nO drag�o lan�a uma rajada de fogo incadescente. \n O seu corpo � incinerado pelas chamas.\n";
        danoTotal = dado1+dado2+dado3+dado4+4;
        cout << "Voc� recebe " << danoTotal;
    }
    return danoTotal;
}

TabelaHash inimigos;

void sala1(){
    string choice;
    int dano = 0;
    int aux = 0;
    bool goblinmorto=false;
    vector<string> goblin = {
R"(             ,      ,)",
R"(            /(.-""-.)\)",
R"(        |\  \/      \/  /|)",
R"(        | \ / =.  .= \ / |)",
R"(        \( \   o\/o   / )/)",
R"(         \_, '-/  \-' ,_/)",
R"(           /   \__/   \)",
R"(           \ \__/\__/ /)",
R"(         ___\ \|--|/ /___)",
R"(       /`    \      /    `\)",
R"(      /       '----'       \)"
};
    for (size_t i = 0; i < goblin.size(); ++i) {
        cout << goblin[i] << "\n";
    }
    cout << "\nUm goblin est� se aproximando!\n";
    inimigos.inserir("Goblin", 20);
    if(mago){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (cajado){
                dano = danoCajado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (grimorio){
                dano = danoGrimorio();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Goblin",vidaInimigo);
            if(vidaInimigo<=0){
                goblinmorto=true;
            }

            //dano goblin
            if(!goblinmorto && vida > 0){
                dano = danoGoblin();
                vida = vida - dano;
            }

        }while (vidaInimigo > 0 && vida > 0);
    } else if (guerreiro){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (espada){
                dano = danoEspada();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (machado){
                dano = danoMachado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Goblin",vidaInimigo);
            if(vidaInimigo<=0){
                goblinmorto=true;
            }

            //dano goblin
            if(!goblinmorto && vida > 0){
                dano = danoGoblin();
                vida = vida - dano;
            }

        }while (!goblinmorto && vida > 0);
    }
        inimigos.remover("Goblin");
    if (vida > 0){
        cout << "\nParab�ns Vlad�o! Voc� passou pelo inimigo do Covil do Goblin!\n";
        completa1 = true;
        cout << "\nAp�s uma �rdua batalha Vlad�o descansa para recuperar suas for�as!\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        recuperar = distrib(gen);
        vida = vida + 100;
        if (pocao && guerreiro && vida > 105){
            vida = 105;
        } else if (pocao && mago && vida > 80){
            vida = 80;
        } else if (!pocao && guerreiro && vida > 95){
            vida = 95;
        } else if (!pocao && mago && vida > 70){
            vida = 70;
        }
        cout << "\nVoc� recuperou " << recuperar << " pontos de vida.\nVida atual: " << vida << "\n";
    }
}

void sala2(){
    string choice;
    int dano = 0;
    int aux = 0;
    bool esqueletomorto=false;
    vector<string> esqueleto = {
R"(                              _.--""-._)",
R"(  .                         ."         ".)",
R"( / \    ,^.         /(     Y             |      )\)",
R"(/   `---. |--'\    (  \__..'--   -   -- -'""-.-'  ))",
R"(|        :|    `>   '.     l_..-------.._l      .')",
R"(|      __l;__ .'      "-.__.||_.-'v'-._||`"----")",
R"( \  .-' | |  `              l._       _.')",
R"(  \/    | |                   l`^^'^^'j)",
R"(        | |                _   \_____/     _)",
R"(        j |               l `--__)-'(__.--' |)",
R"(        | |               | /`---``-----'"1 |  ,-----. )",
R"(        | |               )/  `--' '---'   \'-'  ___  `-.)",
R"(        | |              //  `-'  '`----'  /  ,-'   I`.  \)",
R"(      _ L |_            //  `-.-.'`-----' /  /  |   |  `. \)",
R"(     '._' / \         _/(   `/   )- ---' ;  /__.J   L.__.\ :)",
R"(      `._;/7(-.......'  /        ) (     |  |            | |)",
R"(      `._;l _'--------_/        )-'/     :  |___.    _._./ ;)",
R"(        | |                 .__ )-'\  __  \  \  I   1   / /)",
R"(        `-'                /   `-\-(-'   \ \  `.|   | ,' /)",
R"(                           \__  `-'    __/  `-. `---'',-')",
R"(                              )-._.-- (        `-----')",
R"(                             )(  l\ o ('..-.)",
R"(                       _..--' _'-' '--'.-. |)",
R"(                __,,-'' _,,-''            \ \)",
R"(               f'. _,,-'                   \ \)",
R"(              ()--  |                       \ \)",
R"(                \.  |                       /  \)",
R"(                  \ \                      |._  |)",
R"(                   \ \                     |  ()|)",
R"(                    \ \                     \  /)",
R"(                     ) `-.                   | |)",
R"(                    // .__)                  | |)",
R"(                 _.//7'                      | |)",
R"(               '---'                         j_| `)",
R"(                                            (| |)",
R"(                                             |  \)",
R"(                                             |lllj)",
R"(                                             |||||)"
    };
    for (size_t i = 0; i < esqueleto.size(); ++i) {
        cout << esqueleto[i] << "\n";
    }
    cout << "\nO poderoso esqueleto Larry est� se aproximando!\n";
    inimigos.inserir("Larry", 15);
    if(mago){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (cajado){
                dano = danoCajado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (grimorio){
                dano = danoGrimorio();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Larry",vidaInimigo);
            if(vidaInimigo<=0){
                esqueletomorto=true;
            }

            //dano Esqueleto
            if(!esqueletomorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }

        }while (vidaInimigo > 0 && vida > 0);
    } else if (guerreiro){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (espada){
                dano = danoEspada();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (machado){
                dano = danoMachado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Larry",vidaInimigo);
            if(vidaInimigo<=0){
               esqueletomorto=true;
            }

            //dano esqueleto
            if(!esqueletomorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }

        }while (!esqueletomorto && vida > 0);
    }
    inimigos.remover("Larry");
    if (vida > 0){
        cout << "\nParab�ns Vlad�o! Voc� passou pelo todo poderoso Larry!\n";
        completa2 = true;
        cout << "\nAp�s uma �rdua batalha Vlad�o descansa para recuperar suas for�as!\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        recuperar = distrib(gen);
        vida = vida + recuperar;
        if (pocao && guerreiro && vida > 105){
            vida = 105;
        } else if (pocao && mago && vida > 80){
            vida = 80;
        } else if (!pocao && guerreiro && vida > 95){
            vida = 95;
        } else if (!pocao && mago && vida > 70){
            vida = 70;
        }
        cout << "\nVoc� recuperou " << recuperar << " pontos de vida.\nVida atual: " << vida << "\n";
    }
}

void sala3(){
    int choice;
    do{
        cout << "\nVlad�o v� apenas um ba� isolado no fundo da sala.\nSer� uma armadilha?\n\nAbrir ba�?\n[1]Sim\n[2]N�o\n";
        cin >> choice;
        if (choice == 1){
            cout << "\nVlad�o se enche de coragem e abre o ba�!\n...\n...\n...\nVlad�o encontrou uma po��o de vida m�xima permanente!\n\nVlad�o a bebe e ganha 10 pontos de vida m�xima permanentes!";
            pocao = true;
            vida = vida + 10;
            cout << "\nVida atualizada: " << vida;
            completa3 = true;
        } else if (choice == 2){
            cout << "\nEsse ba� est� muito suspeito... Melhor deixar quieto!\n";
        }
    } while (choice != 1 && choice !=2);

}

void sala4(){
    string choice;
    int dano = 0;
    int aux = 0;
    bool lobomorto=false;
    bool ogromorto=false;
    vector<string> lobo = {
R"(                              __)",
R"(                            .d$$b)",
R"(                          .' TO$;\)",
R"(                         /  : TP._;)",
R"(                        / _.;  :Tb|)",
R"(                       /   /   ;j$j)",
R"(                   _.-"       d$$$$)",
R"(                 .' ..       d$$$$;)",
R"(                /  /P'      d$$$$P. |\)",
R"(               /   "      .d$$$P' |\^"l)",
R"(             .'           `T$P^"""""  :)",
R"(         ._.'      _.'                ;)",
R"(      `-.-".-'-' ._.       _.-"    .-")",
R"(    `.-" _____  ._              .-")",
R"(   -(.g$$$$$$$b.              .')",
R"(     ""^^T$$$P^)            .(:)",
R"(       _/  -"  /.'         /:/;)",
R"(    ._.'-'`-'  ")/         /;/;)",
R"( `-.-"..--""   " /         /  ;)",
R"(.-" ..--""        -'          :)",
R"(..--""--.-"         (\      .-(\)",
R"(  ..--""              `-\(\/;`)",
R"(    _.                      :)",
R"(                            ;`-)",
R"(                           :\)",
R"(                           ;)"
};
vector<string> ogro = {
R"(                           __,='`````'=/__)",
R"(                          '//  (o) \(o) \ `'         _,-,)",
R"(                          //|     ,_)   (`\      ,-'`_,-\)",
R"(                        ,-~~~\  `'==='  /-,      \==```` \__)",
R"(                       /        `----'     `\     \       \/)",
R"(                    ,-`                  ,   \  ,.-\       \)",
R"(                   /      ,               \,-`\`_,-`\_,..--'\)",
R"(                  ,`    ,/,              ,>,   )     \--`````\)",
R"(                  (      `\`---'`  `-,-'`_,<   \      \_,.--'`)",
R"(                   `.      `--. _,-'`_,-`  |    \)",
R"(                    [`-.___   <`_,-'`------(    /)",
R"(                    (`` _,-\   \ --`````````|--`)",
R"(                     >-`_,-`\,-` ,          |)",
R"(                   <`_,'     ,  /\          /)",
R"(                    `  \/\,-/ `/  \/`\_/V\_/)",
R"(                       (  ._. )    ( .__. ))",
R"(                       |      |    |      |)",
R"(                        \,---_|    |_---./)",
R"(                        ooOO(_)    (_)OOoo)"
};
    for (size_t i = 0; i < lobo.size(); ++i) {
        cout << lobo[i] << "\n";
    }
    for (size_t i = 0; i < ogro.size(); ++i) {
        cout << ogro[i] << "\n";
    }

    cout << "\nUm lobo e um Ogro est�o se aproximando!\n";
    inimigos.inserir("Lobo", 25);
    inimigos.inserir("Ogro",25);
    if(mago){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (cajado){
                dano = danoCajado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (grimorio){
                dano = danoGrimorio();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            if(choice == "Lobo"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Lobo",vidaInimigo);
                if(vidaInimigo<=0){
                    lobomorto=true;
                    inimigos.remover("Lobo");
                    cout << "\nBoa Vlad�o! O lobo foi derrotado!\n";
                }
            } else if (choice == "Ogro"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Ogro",vidaInimigo);
                if(vidaInimigo<=0){
                    ogromorto=true;
                    inimigos.remover("Ogro");
                    cout << "\nBoa Vlad�o! O ogro foi derrotado!\n";
                }
            }

            //dano do lobo contra o vladao
            if(!lobomorto && vida > 0){
                dano = danoLobo();
                vida = vida - dano;
            }
            //dano do ogro contra o vladao
            if(!ogromorto && vida > 0){
                dano = danoOgro();
                vida = vida - dano;
            }

        }while (( !lobomorto || !ogromorto ) && vida > 0);
    } else if (guerreiro){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (espada){
                dano = danoEspada();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (machado){
                dano = danoMachado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }
            if(choice == "Lobo"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Lobo",vidaInimigo);;
                if(vidaInimigo<=0){
                    lobomorto=true;
                }
            } else if (choice == "Ogro"){
                if(vidaInimigo<=0){
                    ogromorto=true;
                }else{
                    vidaInimigo = vidaInimigo - dano;
                    inimigos.atualizar("Ogro",vidaInimigo);
                }
            }

            //dano do lobo contra o vladao
            if(!lobomorto && vida > 0){
                dano = danoLobo();
                vida = vida - dano;
            }
            //dano do ogro contra o vladao
            if(!ogromorto && vida > 0){
                dano = danoOgro();
                vida = vida - dano;
            }

        }while (( !lobomorto || !ogromorto ) && vida > 0);
    }
    inimigos.remover("Lobo");
    inimigos.remover("Ogro");
    if (vida > 0){
        cout << "\nParab�ns Vlad�o! Voc� passou pelos inimigos da 1� Entrada do Dom�nio!\n";
        completa4 = true;
        cout << "\nAp�s uma �rdua batalha Vlad�o descansa para recuperar suas for�as!\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        recuperar = distrib(gen);
        vida = vida + recuperar;
        if (pocao && guerreiro && vida > 105){
            vida = 105;
        } else if (pocao && mago && vida > 80){
            vida = 80;
        } else if (!pocao && guerreiro && vida > 95){
            vida = 95;
        } else if (!pocao && mago && vida > 70){
            vida = 70;
        }
        cout << "\nVoc� recuperou " << recuperar << " pontos de vida.\nVida atual: " << vida << "\n";
    }
}


void sala5(){
    cout << "\nVoc� explora com cuidado, a escurid�o � assustadora e olha de volta para voc�.\nVlad�o sente que est� mais perto do que nunca.\n";
    cout << "\nN�o h� nada aqui, mas tome seu pr�ximo passo com cuidado, o perigo est� ao lado.\n";
    completa5 = true;
}

void sala6(){
    cout << "\nVoc� explora com cuidado, a escurid�o � assustadora e olha de volta para voc�.\nUma sensa��o estranha corre em seu corpo, os sons dos seus passos ecoam por todo o lugar.\n";
    cout << "\nEventualmente voc� se convence de que n�o h� nada por aqui, a sala est� vazia.\n";
    completa6 = true;
}

void sala7(){
    string choice;
    int choice2;
    int dano = 0;
    int aux = 0;
    bool harrymorto=false;
    bool barrymorto=false;
    bool ogromorto=false;
    vector<string> ogro = {
R"(                           __,='`````'=/__)",
R"(                          '//  (o) \(o) \ `'         _,-,)",
R"(                          //|     ,_)   (`\      ,-'`_,-\)",
R"(                        ,-~~~\  `'==='  /-,      \==```` \__)",
R"(                       /        `----'     `\     \       \/)",
R"(                    ,-`                  ,   \  ,.-\       \)",
R"(                   /      ,               \,-`\`_,-`\_,..--'\)",
R"(                  ,`    ,/,              ,>,   )     \--`````\)",
R"(                  (      `\`---'`  `-,-'`_,<   \      \_,.--'`)",
R"(                   `.      `--. _,-'`_,-`  |    \)",
R"(                    [`-.___   <`_,-'`------(    /)",
R"(                    (`` _,-\   \ --`````````|--`)",
R"(                     >-`_,-`\,-` ,          |)",
R"(                   <`_,'     ,  /\          /)",
R"(                    `  \/\,-/ `/  \/`\_/V\_/)",
R"(                       (  ._. )    ( .__. ))",
R"(                       |      |    |      |)",
R"(                        \,---_|    |_---./)",
R"(                        ooOO(_)    (_)OOoo)"
};
vector<string> esqueleto = {
R"(        .-.      )",
R"(       (o.o)   /> )",
R"(        |=|   /  / )",
R"(       __|__ /  /  )",
R"(     //.=|=.\/  /   )",
R"(    // .=|=. \_/    )",
R"(    \\(_=_)        )",
R"(     (:| |:)       )",
R"(      || ||        )",
R"(      () ()        )",
R"(      || ||        )",
R"(      || ||        )",
R"(     ==' '==       )"
};
    cout << "\nVoc� explora com cuidado, estranhamente esta sala parece segura.\n Parece o lugar ideal para descansar.\n";
    do{
        cout << "\nDescansar um pouco para recuperar vida?\n[1]Sim\n[2]N�o\n";
        cin >> choice2;
        if (choice2 == 1){
            cout << "\nVlad�o senta para descansar um pouco.\nPassos estranhos come�am a ecoar pela sala.\nUma sala vazia nesse ponto n�o faria sentido!\n� UMA ARMADILHA!\n";
            for (size_t i = 0; i < ogro.size(); ++i) {
                cout << ogro[i] << "\n";
            }
            for (size_t i = 0; i < esqueleto.size(); ++i) {
                cout << esqueleto[i] << "\n";
            }
            for (size_t i = 0; i < esqueleto.size(); ++i) {
                cout << esqueleto[i] << "\n";
            }
        } else if (choice2 == 2){
            cout << "\nVlad�o n�o pode parar agora, o tesouro lend�rio est� muito pr�ximo.\nPassos estranhos come�am a ecoar pela sala enquanto Vlad�o caminha para a sa�da.\nUma sala vazia nesse ponto n�o faria sentido!\n� UMA ARMADILHA!\n";
            for (size_t i = 0; i < ogro.size(); ++i) {
                cout << ogro[i] << "\n";
            }
            for (size_t i = 0; i < esqueleto.size(); ++i) {
                cout << esqueleto[i] << "\n";
            }
            for (size_t i = 0; i < esqueleto.size(); ++i) {
                cout << esqueleto[i] << "\n";
            }
        }
    }while (choice2 != 1 && choice2 != 2);
    cout << "\nUm ogro e os destemidos esqueletos Harry e Barry est�o se aproximando!\n";
    inimigos.inserir("Harry", 15);
    inimigos.inserir("Barry", 15);
    inimigos.inserir("Ogro",25);
    if(mago){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (cajado){
                dano = danoCajado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (grimorio){
                dano = danoGrimorio();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            if(choice == "Barry"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Barry",vidaInimigo);
                if(vidaInimigo<=0){
                    barrymorto=true;
                    inimigos.remover("Barry");
                    cout << "\nBoa Vlad�o! O destemido esqueleto Barry foi derrotado!\n";
                }
            } else if (choice == "Ogro"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Ogro",vidaInimigo);
                if(vidaInimigo<=0){
                    ogromorto=true;
                    inimigos.remover("Ogro");
                    cout << "\nBoa Vlad�o! O ogro foi derrotado!\n";
                }
            } else if (choice == "Harry"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Harry",vidaInimigo);
                if(vidaInimigo<=0){
                    harrymorto=true;
                    inimigos.remover("Harry");
                    cout << "\nBoa Vlad�o! O destemido esqueleto Harry foi derrotado!\n";
                }
            }

            //dano do harry contra o vladao
            if(!harrymorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }
            //dano do barry contra o vladao
            if(!barrymorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }
            //dano do ogro contra o vladao
            if(!ogromorto && vida > 0){
                dano = danoOgro();
                vida = vida - dano;
            }

        }while (( !barrymorto || !ogromorto || !harrymorto) && vida > 0);
    } else if (guerreiro){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (espada){
                dano = danoEspada();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (machado){
                dano = danoMachado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            if(choice == "Barry"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Barry",vidaInimigo);
                if(vidaInimigo<=0){
                    barrymorto=true;
                    inimigos.remover("Barry");
                    cout << "\nBoa Vlad�o! O destemido esqueleto Barry foi derrotado!\n";
                }
            } else if (choice == "Ogro"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Ogro",vidaInimigo);
                if(vidaInimigo<=0){
                    ogromorto=true;
                    inimigos.remover("Ogro");
                    cout << "\nBoa Vlad�o! O ogro foi derrotado!\n";
                }
            } else if (choice == "Harry"){
                vidaInimigo = vidaInimigo - dano;
                inimigos.atualizar("Harry",vidaInimigo);
                if(vidaInimigo<=0){
                    harrymorto=true;
                    inimigos.remover("Harry");
                    cout << "\nBoa Vlad�o! O destemido esqueleto Harry foi derrotado!\n";
                }
            }

            //dano do harry contra o vladao
            if(!harrymorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }
            //dano do barry contra o vladao
            if(!barrymorto && vida > 0){
                dano = danoEsqueleto();
                vida = vida - dano;
            }
            //dano do ogro contra o vladao
            if(!ogromorto && vida > 0){
                dano = danoOgro();
                vida = vida - dano;
            }

        }while (( !barrymorto || !ogromorto || !harrymorto) && vida > 0);
    }
    inimigos.remover("Harry");
    inimigos.remover("Barry");
    inimigos.remover("Ogro");
    if (vida > 0){
        cout << "\nParab�ns Vlad�o! Voc� passou pela emboscada da Sala Vazia!\n";
        completa7 = true;
        cout << "\nAp�s uma �rdua batalha Vlad�o descansa para recuperar suas for�as!\n";
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1, 10);
        recuperar = distrib(gen);
        vida = vida + recuperar;
        if (pocao && guerreiro && vida > 105){
            vida = 105;
        } else if (pocao && mago && vida > 80){
            vida = 80;
        } else if (!pocao && guerreiro && vida > 95){
            vida = 95;
        } else if (!pocao && mago && vida > 70){
            vida = 70;
        }
        cout << "\nVoc� recuperou " << recuperar << " pontos de vida.\nVida atual: " << vida << "\n";
        cout << "\nEnquanto sa�a da sala uma luz dourada � emitida de uma brecha da caverna iluminando todo o corpo de Vlad�o.\nVlad�o se sente mais forte do que nunca!\n";
        cout << "\nVoc� desbloqueou a Ben��o dos Deuses, ser� adicionado 1 dado adicional de ataque para todos os seus ataquer a partir de agora!\n";
        bencaoDeuses = true;
    }
}

void sala8(){
    string choice;
    int dano = 0;
    int aux = 0;
    bool dragaomorto=false;
    vector<string> dragao = {
R"(\/)",
R"(                                        .-'.'`))",
R"(                                     .-' .'  )",
R"(               .                  .-'     `-.          __\/)",
R"(                \.    .  |,   _.-'       -:````)   _.-'.'``))",
R"(                 \`.  |\ | \.-_.           `._ _.-' .'`)",
R"(                __) )__\ |! )/ \_.          _.-'      `.)",
R"(            _.-'__`-' =`:' /.' / |      _.-'      -:`````))",
R"(      __.--' ( (@> ))  = \ ^ `'. |_. .-'           `.)",
R"(     : @       `^^^    == \ ^   `. |<                `.)",
R"(     VvvvvvvvVvvvv)    =  ;   ^  ;_/ :           -:``````))",
R"(       (^^^^^^^^^^=  ==   |      ; \. :            `.)",
R"(    ((  `-----------.  == |  ^   ;_/   :             `.)",
R"(    /\             /==   /       : \.  :     _..--``````))",
R"(  __\ \_          ; ==  /  ^     :_/   :      `.)",
R"(><__   _```---.._/ ====/       ^ : \. :         `.)    )",
R"(    / / `._  ^  ;==   /  ^        :/ .            `.)",
R"(    \/ ((  `._ / === /       ^    `.'       _.--`````))",
R"(    (( /\     ;===  /      ^     .'        `.)",
R"(     __\ \_  : === | ^ /                     `.) )",
R"(  >><__   _``--...__.-'   ^  /  ^              `.)",
R"(       / / `._        ^    .'              .--`````)     .--..)",
R"(       \/   :=`--...____.-'  ^     .___.-'|            .' .--.`.   ()",
R"(      ((    | ===    \                  `.|__.         ; ^:   `.'   ))",
R"(             :  ====  \  ^      ^         `. |          ;  `;   `../__)",
R"(           .-'\====    \    .       ^      `.|___.       ;^  `;       \)",
R"(        .-'    :  ===   \.-'              ^  `.  |        ;  ^ `;      ))",
R"(     .-'    ^   \==== .-'         ^            `.|___.     ;     ;    ()",
R"(  .-'         ^  :=.-'                 ^        `.   |      ;     ;)",
R"(.'      ^       .-'          ^               ^    ;_/__.    ;  ^   ;)",
R"(: ^        ^ .-'     ^                   ^   ;     ;   |    ;       ;)",
R"(:    ^    .-'    ^          ^      ^     _.-'    ^  ;_/    ; ^      ;)",
R"(:  ^    .'                           _.-"    ^      ; \.  ;      ^  ;)",
R"( `.   ^ :   ^         ^       ^__.--"               ;_/  ;          ;)",
R"(   `.^  :                __.--"\         ^     ^    ; \ ;     ^     ;)",
R"(     `-.:       ^___.---"\ ===  \   ^               ;_/'        ^  ;)",
R"(        ``.^         `.   `\===  \         ^     ^       ^        ;)",
R"(           `.     ^    `.   `-. ==\                          ^   ;)",
R"(            _`-._        `.    `\= \    ^           ^           ;)",
R"(    __..--''    _`-._^     `.    `-.`\         ^          ^    ;)",
R"(   (-(-(-(-(--'' jgs `-._  ^ `.     `\`\              ^      .')",
R"(                 __..---''     `._     `-. ^      ^      ^ .')",
R"(        __..---''    ___....---'`-`)      `---...____..---')",
R"(       (-(-(-(-(---''           )"
};
vector<string> artefinal = {
R"(/\)",
R"(                        ||)",
R"(                        ||)",
R"(                        ||)",
R"(                        ||                                               ~-----~)",
R"(                        ||                                            /===--  ---~~~)",
R"(                        ||                   ;'                 /==~- --   -    ---~~~)",
R"(                        ||                (/ ('              /=----         ~~_  --(  ')",
R"(                        ||             ' / ;'             /=----               \__~)",
R"(     '                ~==_=~          '('             ~-~~      ~~~~        ~~~--\~')",
R"(     \\                (c_\_        .i.             /~--    ~~~--   -~     (     ')",
R"(      `\               (}| /       / : \           / ~~------~     ~~\   ()",
R"(      \ '               ||/ \      |===|          /~/             ~~~ \ \()",
R"(      ``~\              ~~\  )~.~_ >._.< _~-~     |`_          ~~-~     )\)",
R"(       '-~                 {  /  ) \___/ (   \   |` ` _       ~~         ')",
R"(       \ -~\                -<__/  -   -  L~ -;   \\    \ _ _/)",
R"(       `` ~~=\                  {    :    }\ ,\    ||   _ :()",
R"(        \  ~~=\__                \ _/ \_ /  )  } _//   ( `|' )",
R"(        ``    , ~\--~=\           \     /  / _/ / '    (   ')",
R"(         \`    } ~ ~~ -~=\   _~_  / \ / \ )^ ( // :_  / ')",
R"(         |    ,          _~-'   '~~__-_  / - |/     \ ()",
R"(          \  ,_--_     _/              \_'---', -~ .   \)",
R"(           )/      /\ / /\   ,~,         \__ _}     \_  "~_)",
R"(           ,      { ( _ )'} ~ - \_    ~\  (-:-)       "\   ~ )",
R"(                  /'' ''  )~ \~_ ~\   )->  \ :|    _,       " )",
R"(                 (\  _/)''} | \~_ ~  /~(   | :)   /          })",
R"(                <``  >;,,/  )= \~__ {{{ '  \ =(  ,   ,       ;)",
R"(               {o_o }_/     |v  '~__  _    )-v|  "  :       ,")",
R"(               {/"\_)       {_/'  \~__ ~\_ \\_} '  {        /~\)",
R"(               ,/!          '_/    '~__ _-~ \_' :  '      ,"  ~ )",
R"(              (''`                  /,'~___~    | /     ,"  \ ~' )",
R"(             '/, )                 (-)  '~____~";     ,"     , })",
R"(           /,')                    / \         /  ,~-"       '~')",
R"(       (  ''/                     / ( '       /  /          '~')",
R"(    ~ ~  ,, /) ,                 (/( \)      ( -)          /~')",
R"(  (  ~~ )`  ~}                   '  \)'     _/ /           ~')",
R"( { |) /`,--.(  }'                    '     (  /          /~')",
R"((` ~ ( c|~~| `}   )                        '/:\         ,')",
R"( ~ )/``) )) '|),                          (/ | \)                 -sjm)",
R"(  (` (-~(( `~`'  )                        ' (/ ')",
R"(   `~'    )'`')                              ')",
R"(     ` ``)"
};

    cout << "\nVoc� entra na sala, e em seu primeiro passo n�o h� d�vidas que aqui � o local que tanto procurou, uma sensa��o de al�vio passa por voc�, mas apenas por pouco tempo...\n";
    cout << "O ar � quente, o t�o precioso lend�rio tesouro que todas as lendas apontavam estava logo ali. Com confian�a, voc� se apronta para resgatar sua recompensa, por�m...\n";
    for ( size_t i = 0; i < dragao.size(); ++i) {
        cout << dragao[i] << "\n";
    }
    cout << "Uma criatura imensa pousa do teto do grande sal�o, t�o gigante que emite estrondos a cada passo.\n";
    cout << "Um drag�o flamejante � colocado a sua frente, mas Vlad�o sabe que n�o pode desistir! Voc� se enche de confian�a e inicia o combate.\n";

    inimigos.inserir("Dragao", 50);
    if(mago){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (cajado){
                dano = danoCajado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (grimorio){
                dano = danoGrimorio();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Dragao",vidaInimigo);
            if(vidaInimigo<=0){
                dragaomorto=true;
            }

            //dano dragao
            if(!dragaomorto && vida > 0){
                dano = danoDragao();
                vida = vida - dano;
            }

        }while (vidaInimigo > 0 && vida > 0);
    } else if (guerreiro){
        do{
            cout << "\nVida: " << vida << "\n";
            do{
                cout << "\nDigite o nome do inimigo que Vlad�o ir� atacar!\n";
                inimigos.mostrarTabela();
                cin >> choice;
                aux = inimigos.buscar(choice);
                if (aux == 1000){
                    cout << "\nInimigo n�o encontrado!\nDigite exatamente como est� escrito na tabela de inimigos.\n";
                }
            } while (aux == 1000);
            vidaInimigo = inimigos.buscar(choice);
            if (espada){
                dano = danoEspada();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            } else if (machado){
                dano = danoMachado();
                cout << "\n Isso causou " << dano << " de dano no inimigo!\n";
            }

            vidaInimigo = vidaInimigo - dano;
            inimigos.atualizar("Dragao",vidaInimigo);
            if(vidaInimigo<=0){
                dragaomorto=true;
            }

            //dano dragao
            if(!dragaomorto && vida > 0){
                dano = danoDragao();
                vida = vida - dano;
            }

        }while (!dragaomorto && vida > 0);
    }
        inimigos.remover("Dragao");

    if (vida > 0){
        completa8=true;
        cout << "Voc� conseguiu! Vlad�o derrota o feroz drag�o e coleta o tesouro! \n";
        for (size_t i = 0; i < artefinal.size(); ++i) {
            cout << artefinal[i] << "\n";
        }
        cout << "\nMuito obrigado por testar nosso jogo! Esse trabalho foi pensado em abordar os conceitos de TabelaHash e Grafo.";
        cout << "\nAproveitamos para fazer uma brincadeira e deixar o jogo mais divertido j� que sab�amos que o senhor ia curtir professor, valeu!\n";
    }

}




int main() {
    string* caminho;
    string salas[9] = {"Entrada","Covil do Goblin", "Recanto do Larry","Sala do ba�","1� Entrada do Dom�nio","2� Entrada do Dom�nio","Sala suspeita","Sala vazia","Dom�nio do Drag�o"};
    Grafo caverna(9, salas);
    vector<string> titulo = {
R"( ____   ____.____       _____  ________            _____  ____________   _______________ ______________________ ________________________)",
R"( \   \ /   /|    |     /  _  \ \______ \          /  _  \ \______ \   \ /   /\_   _____/ \      \__    ___/    |   \______   \_   _____/)",
R"(  \   Y   / |    |    /  /_\  \ |    |  \        /  /_\  \ |    |  \   Y   /  |    __)_  /   |   \|    |  |    |   /|       _/|    __)_ )",
R"(   \     /  |    |___/    |    \|    `   \      /    |    \|    `   \     /   |        \/    |    \    |  |    |  / |    |   \|        \)",
R"(    \___/   |_______ \____|__  /_______  /      \____|__  /_______  /\___/   /_______  /\____|__  /____|  |______/  |____|_  /_______  /)",
R"(                    \/       \/        \/               \/        \/                 \/         \/                         \/        \/ )"
};





    /* Entrada -> 0, Covil do Goblin -> 1, Recanto do Larry -> 2, Sala do B�u -> 3,
    1� Entrada do Dom�nio -> 4, 2� Entrada do Dom�nio -> 5, Sala Suspeita -> 6,
    Sala Vazia -> 7, Dom�nio do Drag�o -> 8
    */

    caverna.adicionarAresta(0,1,1); //Entrada -> Covil do Goblin
    caverna.adicionarAresta(0,2,1); //Entrada -> Recanto do Larry
    caverna.adicionarAresta(1,3,1); //Covil do Goblin -> Sala do b�u
    caverna.adicionarAresta(1,4,1); //Covil do Goblin -> 1� Entrada do Dom�nio
    caverna.adicionarAresta(2,5,1); //Recanto do Larry -> 2� Entrada do Dom�nio
    caverna.adicionarAresta(5,7,1); //2� Entrada do Dom�nio -> Sala Vazia
    caverna.adicionarAresta(4,6,1); //1� Entrada do Dom�nio -> Sala Suspeita
    caverna.adicionarAresta(4,8,1); //1� Entrada do Dom�nio -> Dom�nio do Drag�o
    caverna.adicionarAresta(5,8,1); //2� Entrada do Dom�nio -> Dom�nio do Drag�o

    for (size_t i = 0; i < titulo.size(); ++i) {
        cout << titulo[i] << '\n';
    }
    cout << "BEM VINDO AO RPG DO VLAD�O!\n\n";

    cout << "\nVlad�o � um her�i lend�rio de uma terra distante chamada Cefet.\nEle est� em busca de aventuras na caverna dos tesouros, pois nos dom�nios desta se encontra o tesouro mais raro de todos.";
    cout << "\nVoc� guiar� o vlad�o para cumprir seus objetivos.\n\n\nPasse pelos desafios da caverna dos tesouros e guie Vlad�o para a gl�ria!\n\n\n";

    int selecao=0, local=0, destino, selecao2=0;
    int posicao=0;
    int escolha=-1;

    cout << "Qual ser� a classe de vlad�o? \n [1] Guerreiro (+VIDA -DANO) \n [2] Mago(-VIDA +DANO)\n";
    cin >> selecao;
    do{
    if(selecao==1){
        guerreiro = true;
        vida = 95;
        cout << "\nO guerreiro Vlad�o est� pronto para os combates que o esperam!\nVida m�xima: " << vida;
        cout << "\n\nEscolha sua arma: \n [1]Espada(2d8+1) \n [2]Machado(2d6+1), com chance de cr�tico)\n";
        cin >> selecao2;
        if (selecao2 == 1){
            espada = true;
        } else if (selecao == 2) {
            machado = true;
        }
    }else if(selecao==2){
        mago = true;
        vida = 70;
        cout << "\nO mago Vlad�o est� preparado para conjurar magias!\nVida m�xima: " << vida;
        cout << "\n\nEscolha sua arma: \n [1]Cajado(2d10+2) \n [2]Grim�rio(2d8+1, com chance de cr�tico)\n";
        cin >> selecao2;
        if (selecao2 == 1){
            cajado = true;
        } else if (selecao == 2) {
            grimorio = true;
        }
    }
    else{
        cout << "Escolha uma op��o v�lida!\n";
    }
    }while(selecao2!=1 && selecao2!=2);


    cout << "\nVoc� come�a na " << salas[posicao] << "\n";

    do {
        cout << "\nVoc� est� em: " << salas[posicao] << "\n";
        cout << "Sa�das dispon�veis: \n";

        for(int i=0;i<MAX_VERTICES;i++){
            if(caverna.pesoAresta(posicao, i) > 0){
                cout << " [" << i << "] " << salas[i] << "\n";
            }
        }

        cout << "Digite o n�mero da sala para onde quer ir (-1 para sair) \n";
        cin >> escolha;

        if(escolha >= 0 && escolha <= 9){
            if (caverna.pesoAresta(posicao, escolha) > 0){
                cout << "Voc� entrou em: " << salas[escolha] << "\n";
                posicao = escolha;
                switch (posicao){
                    case 1:
                        if (!completa1){
                            sala1();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 2:
                        if (!completa2){
                            sala2();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 3:
                        if (!completa3){
                            sala3();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 4:
                        if (!completa4){
                            sala4();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 5:
                        if (!completa5){
                            sala5();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 6:
                        if (!completa6){
                            sala6();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 7:
                        if (!completa7){
                            sala7();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                    case 8:
                        if (!completa8){
                            sala8();
                        } else {
                            cout << "\nN�o h� mais nada para fazer nesta sala!\n";
                        }
                        break;
                }
            } else {
                cout << "Não há caminhos para a sala escolhida.";
            }
        }

    } while(escolha!=-1 && vida > 0 && !completa8);

    if(vida <= 0){
        cout << "\nVladão foi dominado pelos perigos da caverna dos tesouros e pereceu para a tristeza de todos!\n";
    }

    cout << "\nFim da aventura! \n";

    return 0;
}

























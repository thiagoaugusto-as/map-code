#include<iostream>
#include <typeinfo>
#include <string>
#define TAM_TABLE 120
using namespace std;

// ######## DEFINICOES DA CLASSE DADOS ############ //
class dados
{
    int chave;
    string nome;
public:
    dados()
    {
        chave=-1;
    }
    dados(int k, string n)
    {
        nome = n;
        chave = k;
    }
    friend ostream& operator<<(ostream &out, dados &t)
    {
        out<<" Chave: "<<t.chave;
        out<<" , Nome: "<<t.nome;
        return out;
    }
     friend istream& operator>>(istream &in, dados &t)
    {
        cout<<"\nDigite a chave (int): ";
        in>>t.chave;
        cout<<"Digite o nome: ";
        in>>t.nome;
        return in;
    }
    void setNome(string n)
    {
        nome=n;
    }
     void setChave(int c)
    {
        chave=c;
    }
    int getChave()
    {
        return chave;
    }
};

// ######## DEFINICOES DO NÓ QUE SERA USADO NA LISTA ENCADEADA PARA O MAPA ############ //
template <class K, class T>
class no
{
private:
    no<K,T> *prox;
    T reg;
    K chave;
public:
    no()
    {
        prox=NULL;
    }
    no(K c, T r)
    {
        chave=c;
        reg=r;
        prox=NULL;
    }
    void setProx(no<K,T> *p)
    {
        prox=p;
    }
    void setReg(T r)
    {
        reg=r;
    }
    void setChave(K c)
    {
        chave=c;
    }
    no<K,T>* getProx()
    {
        return prox;
    }
    T& getReg()
    {
        return reg;
    }
    K& getChave()
    {
        return chave;
    }
    void imprime()
    {
        cout<<"Chave no Mapa: [ "<<chave<<" ]"<<endl;
        cout<<"Objeto: [ "<<reg<<" ]"<<endl<<endl;
    }
};
// ############################################ //


// ######## DEFINICOES DO ITERADOR ############ //

// NÓ DO ITERADOR
template <class K, class T>
class noIterator { // o nó do iterador vai ter um ponteiro que aponta para ele mesmo e outro ponteiro do tipo no que irá apontar para o elemento correspondente no mapa
private:
    noIterator<K,T> *prox;
    no<K,T> *dataMap;
public:
    noIterator(no<K,T>* data) {
        prox=nullptr;
        dataMap=data;
    }
    void setDataMap(no<K,T> *data)  {
        dataMap = data;
    }
    void setProx(noIterator<K,T> *p) {
        prox = p;
    }
    no<K,T>* getDataMap() {
        return dataMap;
    }
    noIterator<K,T>* getProx() {
        return prox;
    }
    void imprime()
    {
        cout << "Chave no Mapa: [ " << dataMap->getChave() << " ]"<<endl;
        cout << "Objeto: [ " << dataMap->getReg() << " ] "<<endl<<endl;
    }
};

template<class K, class T>
class iterador {
private:
    noIterator<K,T> *ini, *fim, *atual;
    int tam;
public:
    iterador() {
        ini = nullptr;
        fim = nullptr;
        atual = ini;
        tam = 0;
    }

    noIterator<K,T>* getIni() {
        return ini;
    }

    noIterator<K,T>* getFim() {
        return fim;
    }

    noIterator<K,T>* getAtual() {
        atual = ini;
        return atual;
    }

    void setAtual(noIterator<K,T>* data) {
        atual=data;
    }

    bool vazia() {
        if(ini==fim and ini==nullptr)
            return true;
            else
                return false;
    }

    int transformString(int key) {
        return key;
    }

    int transformString(string key) {
        int aux=0;

        for(int i=0;i<key.size();i++) {
            aux = aux+(int(key.at(i)))*(i+1);
        }

        return aux;
    }

    void insere(no<K,T>* data) //retorna uma pair com o registro e um bool (false, j� est� no mapa, true foi inserido)
    {
        noIterator<K,T> *aux, *p;
        aux = new noIterator<K,T>(data);
        int aux_k,ini_k,fim_k,p_k,pprox_k; //variaveis auxiliares para ajudarem na transformação quando a chave é uma string
        if(vazia()) { // verifica se o iterador esta vazio
            ini=aux;
            fim=aux;
            setAtual(aux);
            tam++;
        } else {

            p=ini;

            while (p->getProx()!=nullptr or tam>=1) {

                //esse primeiro if é responsavel por retornar às variaveis auxiliares a convercao da chave para inteiro
                if(typeid(aux->getDataMap()->getChave()) != typeid(int)) {
                    aux_k = transformString(aux->getDataMap()->getChave());
                    ini_k = transformString(ini->getDataMap()->getChave());
                    fim_k = transformString(fim->getDataMap()->getChave());
                    p_k = transformString(p->getDataMap()->getChave());
                    if(p->getProx()!=nullptr){
                        pprox_k = transformString(p->getProx()->getDataMap()->getChave());
                    }
                } else {
                    aux_k = transformString(aux->getDataMap()->getChave());
                    if(p->getProx()!=nullptr){
                        pprox_k = transformString(p->getProx()->getDataMap()->getChave());
                    }
                    ini_k = transformString(ini->getDataMap()->getChave());
                    fim_k = transformString(fim->getDataMap()->getChave());
                    p_k = transformString(p->getDataMap()->getChave());
                }

                if(aux_k < ini_k) { // insere no inicio
                    aux->setProx(ini);
                    ini=aux;
                    tam++;
                    setAtual(aux);
                    break;
                } else if(aux_k > fim_k){  // insere no fim
                    fim->setProx(aux);
                    fim=aux;
                    tam++;
                    break;
                } else if((p_k < aux_k) and (pprox_k > aux_k)) { // insere no meio
                    aux->setProx(p->getProx());
                    p->setProx(aux);
                    tam++;
                    break;
                }
                p = p->getProx();
            }
        }
    }

    noIterator<K,T>* operator++() { // sobrecarga operador ++
        atual = atual->getProx();
        return atual;
    }

    imprime() {
        noIterator<K,T> *atual;
        for(atual=getIni(); atual!=nullptr; atual = atual->getProx()) {
            atual->imprime();
        }
    }



};
// ############################################ //

// ######## IMPLEMENTACAO DA LISTA ######### //
template <class K, class T>
class lista //lista que sera usada no hash do mapa
{
private:
    no<K,T> *ini, *fim;
public:
    lista()
    {
        ini=NULL;
        fim=NULL;
    }
    bool vazia()
    {
        if(ini==fim && ini==NULL)
            return true;
        else
            return false;
    }
    no<K,T>* insere(K c, T r) //retorna bool (false, ja esta no mapa, true foi inserido)
    {
        no<K,T> *aux;
        aux=ini;

        while(aux!=NULL) //verifica se ja tem um registro com c
        {
            if(aux->getChave()==c) // se tiver retorna o registro da chave c
                return nullptr;

            aux=aux->getProx();
        }

        aux=new no<K,T>(c,r); //como não encontrou cria o no
        if(vazia())
        {;
            ini=aux;
            fim=aux;
        }
        else
        {
            fim->setProx(aux);
            fim=aux;
        }
        return aux;
    }

    void imprime()
    {
        no<K,T> *aux;
        aux=ini;
        cout<<"\nImpressao do Mapa:\n\n";

        if(vazia())
        {
            cout<<"Lista Vazia!!!"<<endl;
            return;
        }
        while(aux!=NULL)
        {
            aux->imprime();
            aux=aux->getProx();
        }
    }

    T& operator [](K m)
    {

        return insere(m,T()).first; //retorna o primeiro elemento retornado pelo insere.

    }
};
// ############################################ //

// ############## IMPLEMENTACAO DO MAPA ################ //
template <class K, class T>
class mapa {
private:
    noIterator<K,T> *atual;
    no<K,T>* aux;
    lista<K,T> *table[TAM_TABLE] = {nullptr}; // Criacao de um vetor de ponteiros para hash
    dados x;
    int index;
    K chave;
public:
    iterador<K,T> it;
    mapa(){
        for(int i=0; i<TAM_TABLE; i++ ) {
            table[i] = new lista<K,T>; //inicialisacao da hash: Um vetor com cada posicao contendo uma lista encadeada
        }
    }

    iterador<K,T> getIt() {
        return it;
    }

    int transformString(int key) { // caso a chave seja um inteiro retorna o index para hash
        return key%TAM_TABLE;
    }

    int transformString(string key) { // converte a chave para um inteiro caso seja uma string
        int aux=0;

        for(int i=0;i<key.size();i++) {
            aux = aux+(int(key.at(i)))*(i+1);
        }

        return aux;
    }

    insere() {

        cout << endl;
        cout << "Chave: ";
        cin >> chave;
        cin >> x;


        if(typeid(chave) == typeid(string)) {
            index = transformString(chave)%TAM_TABLE;
        } else {
            index = transformString(chave);
        }

        aux = table[index]->insere(chave,x); // insere elemento na hash

        if(aux!=nullptr) // insere elemento no iterator, caso aux seja null não vai inserir
            it.insere(aux);
            else
                cout << endl << "Esse registro ja existe!";

        it.imprime();
    }
};
// ############################################ //

int main()
{

    mapa<string,dados> mapa; //cria um mapa
    noIterator<string,dados>* atual; // variavel do tipo no do iterator para auxiliar na impressao
    int out;



    do {
        mapa.insere();
        cout << endl << endl << "Sair [0]? ";
        cin >> out;
    }while(out!=0);

    system("cls");
    cout << endl << "MAPA:";
    for(atual = mapa.it.getIni(); atual != nullptr; atual = ++mapa.it) {
        cout << endl << endl << "Chave: ";
        cout << atual->getDataMap()->getChave();
        cout << endl << "Objeto:";
        cout  << atual->getDataMap()->getReg();
    }

    return 0;
}


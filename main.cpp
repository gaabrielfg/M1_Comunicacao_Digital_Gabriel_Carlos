//Carlos Natham Domingos e Gabriel Farias Goi
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    setlocale(LC_ALL,"Portuguese");
    int resp, resp2, resp3, i, aleatorio, aleatorio2, aleatorio3;  // variaveis de resposta e valor aleatorio
    int palavra1[11], palavra0[8], val_redundante1[15], val_redundante0[12], erro1[4], erro0[4]; // vetores que vão receber as palavras de entrada, a mensagem e o erro
    int msg1 [11] = {1,0,1,0,1,0,1,0,1,0,1}; // mensagens a ser enviadas no checksum
    int msg2 [11] = {1,1,0,0,1,1,0,0,1,1,1};
    int msg3 [11] = {1,0,1,1,1,1,0,0,1,1,1};
    int soma1[11] = {0,0,0,0,0,0,0,0,0,0,0}; // vetores de respostas das somas de verificação
    int soma2[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int soma3[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int soma4[11] = {0,0,0,0,0,0,0,0,0,0,0};
    int vaium = 0;//variável de overflow;
    int aux[11] = {0,0,0,0,0,0,0,0,0,0,1};// variável para somar caso de overflow
    int soma; // variavel auxiliar para soma de binario

    cout << "Escolha qual opcao deseja realizar:" << endl; // menu de escolha da operação
    cout << "[0] Hamming(12,8)" << endl;
    cout << "[1] Hamming(15,11)" << endl; // codigo de aluno usado: 6444911 (Carlos Natham Domingos), onde soma é 9+1+1 = 11 bits
    cout << "[2] Checksum" << endl;
    cout << "Sua opcao: "; //6+4+4+4+9+1+1 = 29 bits - impar
    cin >> resp;

    switch(resp)
    {
    case 0: //hamming 12,8
        cout << "Informe sua palavra: " << endl; // salvar a palavra digitada
        cin >> palavra0[0];
        cin >> palavra0[1];
        cin >> palavra0[2];
        cin >> palavra0[3];
        cin >> palavra0[4];
        cin >> palavra0[5];
        cin >> palavra0[6];
        cin >> palavra0[7];

        // faz os calculos dos bits de paridade usando o operador de xor (^) para posições x0, x1, x3 e x7
        val_redundante0[0] = palavra0[0] ^ palavra0[1] ^ palavra0[3] ^ palavra0[4] ^ palavra0[6];
        val_redundante0[1] = palavra0[0] ^ palavra0[2] ^ palavra0[3] ^ palavra0[5] ^ palavra0[6];
        val_redundante0[2] = palavra0[0];
        val_redundante0[3] = palavra0[1] ^ palavra0[2] ^ palavra0[3] ^ palavra0[7];
        val_redundante0[4] = palavra0[1];
        val_redundante0[5] = palavra0[2];
        val_redundante0[6] = palavra0[3];
        val_redundante0[7] = palavra0[4] ^ palavra0[5] ^ palavra0[6] ^ palavra0[7];
        val_redundante0[8] = palavra0[4];
        val_redundante0[9] = palavra0[5];
        val_redundante0[10] = palavra0[6];
        val_redundante0[11] = palavra0[7];

        // exibe a mensagem enviada
        cout << "Mensagem Enviada: ";
        for(i = 0; i<12; i ++)
        {
            cout << val_redundante0[i];
        }

        // escolha para injetar ou não um erro
        cout << endl;
        cout << "Deseja Injetar um erro?" << endl;
        cout << "[0] Nao" << endl;
        cout << "[1] Sim" << endl;
        cout << "Sua opcao: ";
        cin >> resp2;

        // define um valor aleatorio e usa ele como posição para simular uma inversão de bits
        if(resp2 == 1)
        {
            srand((unsigned)time(0));
            aleatorio = rand()%(12);
            if(val_redundante0[aleatorio] == 0)  // se o bit na posição aleatoria for 0, inverte para 1
            {
                val_redundante0[aleatorio] = 1;
            }
            else
            {
                val_redundante0[aleatorio] = 0; // se o bit na posição aleatoria for 1, inverta para 0
            }
        }

        // usando o vetor de erro, faz o calculo de detecção de erro, usando a proprio bit de paridade na operação de xor
        erro0[0] = val_redundante0[0] ^ val_redundante0[2] ^ val_redundante0[4] ^ val_redundante0[6] ^ val_redundante0[8] ^ val_redundante0[10];
        erro0[1] = val_redundante0[1] ^ val_redundante0[2] ^ val_redundante0[5] ^ val_redundante0[6] ^ val_redundante0[9] ^ val_redundante0[10];
        erro0[2] = val_redundante0[3] ^ val_redundante0[4] ^ val_redundante0[5] ^ val_redundante0[6] ^ val_redundante0[11];
        erro0[3] = val_redundante0[7] ^ val_redundante0[8] ^ val_redundante0[9] ^ val_redundante0[10] ^ val_redundante0[11];

        cout << endl;

        if(erro0[0] == 0 && erro0[1] == 0 && erro0[2] == 0 && erro0[3] == 0)  // se for tudo 0 no vetor de erro, significa que não tem erro
        {
            cout << "Mensagem Recebida: ";
            for(i = 0; i<12; i ++)
            {
                cout << val_redundante0[i];
            }
            cout << endl;
            cout << "Sem erro: ";   // exibe k7k3k1k0, sendo todos 0 por não ter erro
            for(i = 3; i>=0; i --)
            {
                cout << erro0[i];
            }
        }
        else   // se caso foi escolhido a injeção de erro, ele vai para esta parte
        {
            cout << "Mensagem Recebida: ";
            for(i = 0; i<12; i ++)
            {
                cout << val_redundante0[i];
            }
            cout << endl;
            cout << "Erro Detectado: "; // exibe o vetor de erro com a posição em binario de onde esta o erro
            for(i = 3; i>=0; i --)
            {
                cout << erro0[i];
            }
            cout << " - Posicao: " << (erro0[3] * 8) + (erro0[2] * 4) + (erro0[1] * 2) + erro0[0] << endl; // converte o valor para decimal

            //faz a correção do bit o invertendo novamente
            if(val_redundante0[aleatorio] == 0)
            {
                val_redundante0[aleatorio] = 1;
            }
            else
            {
                val_redundante0[aleatorio] = 0;
            }

            //exibe mensagem corrigida
            cout << "Mensagem Corrigida: ";
            for(i = 0; i<12; i ++)
            {
                cout << val_redundante0[i];
            }
            cout << endl;
        }
        break;
    case 1: //hamming 15,11
        cout << "Informe sua palavra: " << endl; // salvar a palavra digitada
        cin >> palavra1[0];
        cin >> palavra1[1];
        cin >> palavra1[2];
        cin >> palavra1[3];
        cin >> palavra1[4];
        cin >> palavra1[5];
        cin >> palavra1[6];
        cin >> palavra1[7];
        cin >> palavra1[8];
        cin >> palavra1[9];
        cin >> palavra1[10];

        // faz os calculos dos bits de paridade usando o operador de xor (^) para posições x0, x1, x3 e x7
        val_redundante1[0] = palavra1[0] ^ palavra1[1] ^ palavra1[3] ^ palavra1[4] ^ palavra1[6] ^ palavra1[8] ^ palavra1[10];
        val_redundante1[1] = palavra1[0] ^ palavra1[2] ^ palavra1[3] ^ palavra1[5] ^ palavra1[6] ^ palavra1[9] ^ palavra1[10];
        val_redundante1[2] = palavra1[0];
        val_redundante1[3] = palavra1[1] ^ palavra1[2] ^ palavra1[3] ^ palavra1[7] ^ palavra1[8] ^ palavra1[9] ^ palavra1[10];
        val_redundante1[4] = palavra1[1];
        val_redundante1[5] = palavra1[2];
        val_redundante1[6] = palavra1[3];
        val_redundante1[7] = palavra1[4] ^ palavra1[5] ^ palavra1[6] ^ palavra1[7] ^ palavra1[8] ^ palavra1[9] ^ palavra1[10];
        val_redundante1[8] = palavra1[4];
        val_redundante1[9] = palavra1[5];
        val_redundante1[10] = palavra1[6];
        val_redundante1[11] = palavra1[7];
        val_redundante1[12] = palavra1[8];
        val_redundante1[13] = palavra1[9];
        val_redundante1[14] = palavra1[10];

        // exibe a mensagem enviada
        cout << "Mensagem Enviada: ";
        for(i = 0; i<15; i ++)
        {
            cout << val_redundante1[i];
        }

        // escolha para injetar ou não um erro
        cout << endl;
        cout << "Deseja Injetar um erro?" << endl;
        cout << "[0] Nao" << endl;
        cout << "[1] Sim" << endl;
        cout << "Sua opcao: ";
        cin >> resp2;

        // define um valor aleatorio e usa ele como posição para simular uma inversão de bits
        if(resp2 == 1)
        {
            srand((unsigned)time(0));
            aleatorio = rand()%(12);
            if(val_redundante1[aleatorio] == 0)  // se o bit na posição aleatoria for 0, inverte para 1
            {
                val_redundante1[aleatorio] = 1;
            }
            else
            {
                val_redundante1[aleatorio] = 0; // se o bit na posição aleatoria for 1, inverte para 0
            }
        }

        // usando o vetor de erro, faz o calculo de detecção de erro, usando a proprio bit de paridade na operação de xor
        erro1[0] = val_redundante1[0] ^ val_redundante1[2] ^ val_redundante1[4] ^ val_redundante1[6] ^ val_redundante1[8] ^ val_redundante1[10] ^ val_redundante1[12] ^ val_redundante1[14];
        erro1[1] = val_redundante1[1] ^ val_redundante1[2] ^ val_redundante1[5] ^ val_redundante1[6] ^ val_redundante1[9] ^ val_redundante1[10] ^ val_redundante1[13] ^ val_redundante1[14];
        erro1[2] = val_redundante1[3] ^ val_redundante1[4] ^ val_redundante1[5] ^ val_redundante1[6] ^ val_redundante1[11] ^ val_redundante1[12] ^ val_redundante1[13] ^ val_redundante1[14];
        erro1[3] = val_redundante1[7] ^ val_redundante1[8] ^ val_redundante1[9] ^ val_redundante1[10] ^ val_redundante1[11] ^ val_redundante1[12] ^ val_redundante1[13] ^ val_redundante1[14];

        cout << endl;

        if(erro1[0] == 0 && erro1[1] == 0 && erro1[2] == 0 && erro1[3] == 0)  // se for tudo 0 no vetor de erro, significa que não tem erro
        {
            cout << "Mensagem Recebida: ";
            for(i = 0; i<15; i ++)
            {
                cout << val_redundante1[i];
            }
            cout << endl;
            cout << "Sem erro: "; // exibe k7k3k1k0, sendo todos 0 por não ter erro
            for(i = 3; i>=0; i --)
            {
                cout << erro1[i];
            }
        }
        else   // se caso foi escolhido a injeção de erro, ele vai para esta parte
        {
            cout << "Mensagem Recebida: ";
            for(i = 0; i<15; i ++)
            {
                cout << val_redundante1[i];
            }
            cout << endl;
            cout << "Erro Detectado: "; // exibe o vetor de erro com a posição em binario de onde esta o erro
            for(i = 3; i>=0; i --)
            {
                cout << erro1[i];
            }
            cout << " - Posicao: " << (erro1[3] * 8) + (erro1[2] * 4) + (erro1[1] * 2) + erro1[0] << endl; // converte o valor para decimal

            //faz a correção do bit o invertendo novamente
            if(val_redundante1[aleatorio] == 0)
            {
                val_redundante1[aleatorio] = 1;
            }
            else
            {
                val_redundante1[aleatorio] = 0;
            }

            //exibe mensagem corrigida
            cout << "Mensagem Corrigida: ";
            for(i = 0; i<15; i ++)
            {
                cout << val_redundante1[i];
            }
            cout << endl;
        }
        break;
    case 2:
        //procedimento para o Tx
        for(i=10; i>=0; i--) // soma da mensagem 1 com a mensagem 2
        {
            soma = msg1[i] + msg2[i] + vaium;
            if(soma == 0)
            {
                soma1[i] = 0;
                vaium = 0;
            }
            else if(soma == 1)
            {
                soma1[i] = 1;
                vaium = 0;
            }
            else if(soma == 2)
            {
                soma1[i] = 0;
                vaium = 1;
            }
            else
            {
                soma1[i] = 1;
                vaium = 1;
            }
        }

        soma = 0; // zera variavel auxiliar de soma

        if(vaium == 1)  // verifica se teve overflow na soma passada
        {
            vaium=0;
            for(i=10; i>=0; i--) // se teve, faz a soma da resposta mais 1
            {
                soma = soma1[i] + aux[i] + vaium;
                if(soma == 0)
                {
                    soma1[i] = 0;
                    vaium = 0;
                }
                else if(soma == 1)
                {
                    soma1[i] = 1;
                    vaium = 0;
                }
                else if(soma == 2)
                {
                    soma1[i] = 0;
                    vaium = 1;
                }
                else
                {
                    soma1[i] = 1;
                    vaium = 1;
                }
            }
        }

        soma = 0; // zera variavel auxiliar de soma

        for(i=10; i>=0; i--) // soma da resposta anterior mais a mensagem 3
        {
            soma = soma1[i] + msg3[i] + vaium;
            if(soma == 0)
            {
                soma2[i] = 0;
                vaium = 0;
            }
            else if(soma == 1)
            {
                soma2[i] = 1;
                vaium = 0;
            }
            else if(soma == 2)
            {
                soma2[i] = 0;
                vaium = 1;
            }
            else
            {
                soma2[i] = 1;
                vaium = 1;
            }
        }

        soma = 0; //zera variavel auxiliar de soma

        if(vaium == 1)  // verifica se teve overflow na soma passada
        {
            vaium = 0;
            for(i=10; i>=0; i--) // se teve, faz a soma da resposta mais 1
            {
                soma = soma2[i] + aux[i] + vaium;
                if(soma == 0)
                {
                    soma2[i] = 0;
                    vaium = 0;
                }
                else if(soma == 1)
                {
                    soma2[i] = 1;
                    vaium = 0;
                }
                else if(soma == 2)
                {
                    soma2[i] = 0;
                    vaium = 1;
                }
                else
                {
                    soma2[i] = 1;
                    vaium = 1;
                }
            }
        }

        for(i=10; i>=0; i--) // faz o complemente de 1 com a resposta das somas
        {
            if(soma2[i] == 0)
                soma3[i] = 1;
            else
                soma3[i] = 0;
        }

        cout << "EDC (TX): ";
        for(i = 0; i<11; i++)
        {
            cout << soma3[i];
        }

        cout << endl;
        cout << "Deseja Injetar um erro?" << endl;
        cout << "[0] Não" << endl;
        cout << "[1] Sim" << endl;
        cout << "Sua opção: ";
        cin >> resp3;
        

        if(resp3 == 1)
        {
            srand((unsigned)time(0));
            aleatorio2 = rand()%(3); // varivel aleatoria para escolher qual das palavras sofrera injeção de erro
            aleatorio3 = rand()%(12); // variavel aleatoria para escolher a posição do vetor da mensagem escolhida que sera modificada
            if(aleatorio2 == 0)  // se for 0, a mensagem 1 sofrera a injeção do erro
            {
                if(msg1[aleatorio3] == 0)  // se o bit na posição aleatoria for 0, inverte para 1
                {
                    msg1[aleatorio3] = 1;
                }
                else
                {
                    msg1[aleatorio3] = 0; // se o bit na posição aleatoria for 1, inverta para 0
                }
            }
            else if(aleatorio2 == 1)   // se for 1, a mensagem 2 sofrera a injeção do erro
            {
                if(msg2[aleatorio3] == 0)  // se o bit na posição aleatoria for 0, inverte para 1
                {
                    msg2[aleatorio3] = 1;
                }
                else
                {
                    msg2[aleatorio3] = 0; // se o bit na posição aleatoria for 1, inverta para 0
                }
            }
            else   // se for 2, a mensagem 3 sofrera a injeção do erro
            {
                if(msg3[aleatorio3] == 0)  // se o bit na posição aleatoria for 0, inverte para 1
                {
                    msg3[aleatorio3] = 1;
                }
                else
                {
                    msg3[aleatorio3] = 0; // se o bit na posição aleatoria for 1, inverta para 0
                }
            }
        }
        // novamente o mesmo procedimento para o Rx
        for(i=10; i>=0; i--) // soma da mensagem 1 com a mensagem 2
        {
            soma = msg1[i] + msg2[i] + vaium;
            if(soma == 0)
            {
                soma1[i] = 0;
                vaium = 0;
            }
            else if(soma == 1)
            {
                soma1[i] = 1;
                vaium = 0;
            }
            else if(soma == 2)
            {
                soma1[i] = 0;
                vaium = 1;
            }
            else
            {
                soma1[i] = 1;
                vaium = 1;
            }
        }

        soma = 0; // zera variavel auxiliar de soma

        if(vaium == 1)  // verifica se teve overflow na soma passada
        {
            vaium=0;
            for(i=10; i>=0; i--) // se teve, faz a soma da resposta mais 1
            {
                soma = soma1[i] + aux[i] + vaium;
                if(soma == 0)
                {
                    soma1[i] = 0;
                    vaium = 0;
                }
                else if(soma == 1)
                {
                    soma1[i] = 1;
                    vaium = 0;
                }
                else if(soma == 2)
                {
                    soma1[i] = 0;
                    vaium = 1;
                }
                else
                {
                    soma1[i] = 1;
                    vaium = 1;
                }
            }
        }

        soma = 0; // zera variavel auxiliar de soma

        for(i=10; i>=0; i--) // soma da resposta anterior mais a mensagem 3
        {
            soma = soma1[i] + msg3[i] + vaium;
            if(soma == 0)
            {
                soma2[i] = 0;
                vaium = 0;
            }
            else if(soma == 1)
            {
                soma2[i] = 1;
                vaium = 0;
            }
            else if(soma == 2)
            {
                soma2[i] = 0;
                vaium = 1;
            }
            else
            {
                soma2[i] = 1;
                vaium = 1;
            }
        }

        soma = 0; //zera variavel auxiliar de soma

        if(vaium == 1)  // verifica se teve overflow na soma passada
        {
            vaium = 0;
            for(i=10; i>=0; i--) // se teve, faz a soma da resposta mais 1
            {
                soma = soma2[i] + aux[i] + vaium;
                if(soma == 0)
                {
                    soma2[i] = 0;
                    vaium = 0;
                }
                else if(soma == 1)
                {
                    soma2[i] = 1;
                    vaium = 0;
                }
                else if(soma == 2)
                {
                    soma2[i] = 0;
                    vaium = 1;
                }
                else
                {
                    soma2[i] = 1;
                    vaium = 1;
                }
            }
        }

        soma = 0; //zera variavel auxiliar de soma
        vaium = 0; //zera variavel auxiliar de overflow

        for(i=10; i>=0; i--) // somas de verificação de Rx agora serão somadas com o EDC de Tx
        {
            soma = soma2[i] + soma3[i] + vaium;
            if(soma == 0)
            {
                soma4[i] = 0;
                vaium = 0;
            }
            else if(soma == 1)
            {
                soma4[i] = 1;
                vaium = 0;
            }
            else if(soma == 2)
            {
                soma4[i] = 0;
                vaium = 1;
            }
            else
            {
                soma4[i] = 1;
                vaium = 1;
            }
        }

        cout << endl;

        // verificando se a resposta final está com ou sem erros
        if(soma4[0] == 1 && soma4[1] == 1 && soma4[2] == 1 && soma4[3] == 1 && soma4[4] == 1 && soma4[5] == 1 && soma4[6] == 1 && soma4[7] == 1 && soma4[8] == 1 && soma4[9] == 1 && soma4[10] == 1)
        {
            cout << "Mensagem final (Rx): ";
            for(i = 0; i<11; i++)
            {
                cout << soma4[i];
            }
            cout << " - Sem Erros";
        }
        else
        {
            cout << "Mensagem final (Rx): ";
            for(i = 0; i<11; i++)
            {
                cout << soma4[i];
            }
            cout << " - Com Erros";
        }

        break;
    }
    return 0;
}
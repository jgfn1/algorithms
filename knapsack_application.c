/*
* DESCRIÇÃO DO PROBLEMA | PROBLEM DESCRIPTION
*
* PORTUGUÊS:
* Um pai deseja levar o filho ao parque de diversões e divertí-lo o máximo possível.
* O parque possui N brinquedos, numerados de 0 a N-1, cada um com um custo diferente
* de C[i] créditos por corrida. O atencioso pai percebeu que o seu filho possui lá
* suas preferências e atribuiu a cada brinquedo um índice inicial de diversão S[i]
* para i=0,...,N-1. A criança pode andar mais de uma vez em cada brinquedo, mas o pai
* também percebeu que a empolgação vai diminuindo rapidamente a cada corrida.
* Ele associou a cada brinquedo um fator de aborrecimento B[i], e estimou que a diversão
* obtida na k-ésima corrida no brinquedo i decai para F(i,k)=S[i]-(k-1)²*B[i],
* para k=1,2,3,..., sendo a diversão considerada nula assim que esse valor de F(i,k)
* torna-se <=0. Sabendo que o pai só dispõe de um cartão com uma quantidade limitada
* de créditos K, sua tarefa é ajudá-lo a escolher os brinquedos que resultem na maior diversão possível.
*
*
*ENGLISH:
*A father wants to take his son to the park and make him have as much fun as possible.
*The park has N attractions, numbered from 0 to N - 1, each one with a different cost of C[i] credits per round.
*The kind father knows his child preferences and assigned an initial fun index S[i](i = 0, ..., N - 1) for each
*attraction. The kid can play on each of them more than once, but the father realized the fun shrinks at each
*round played so he associated a boredom factor B[i] and estimated that the fun had in the kth round on an
*attraction decays for F(i, k) = S[i] - ((k - 1)^2 * B[i]), knowing that k = 1, 2, 3, ..., and the fun ends
*when the value of F(i, k) is <= 0. Given that the father has a limited card with credit K, your job is to help him
*choose the attractions which will maximize his son's fun at the park.
*/


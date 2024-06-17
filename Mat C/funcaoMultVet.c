float MultMat(float V1[10], float V2[10]){
	float Vresult[10];
	int cont;
	for(cont = 0; cont < 10; cont++)
		Vresult[cont] = V1[cont] * V2[cont];
	return Vresult;
}
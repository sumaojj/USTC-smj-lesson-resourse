#include "Exercise.h"
clock_t start, end;


void exercise_1()
{
	int N = 84; //矩阵大小
	vector<vector<double>> A(N, vector<double>(N));
	vector<double> b(N);

	//初始化A和b
	for (int i = 0; i < N - 1; i++)
	{
		A[i][i] = 6;
		A[i + 1][i] = 8;
		A[i][i + 1] = 1;
		b[i+1] = 15;
	}
	A[N - 1][N - 1] = 8;
	b[0] = 7;
	b[N - 1] = 14;
	
	vector<vector<double>> A_1=A; vector<double> b_1=b; //copy otherwise change A b values

	//gauss eml
	start=clock();

	gauss_elim(A_1);// now  LU in A

	forward_subs1(A_1,b_1);// now b_1=Ux=y 

	back_subs(A_1,b_1);//now b_1=x

	end=clock();
	std::cout<<"time_gauss = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);



	//gauss eml full
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	vector<int> u(N-1);	vector<int> v(N-1);

	gauss_elim_full_pivoting(A_1,u,v);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*Q^-1*x

	back_subs(A_1,b_1);//now b_1=Q^-1*x

	vector_qb(v,b_1);

	end=clock();
	std::cout<<"time_gauss full = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  
	std::cout<<"time_gauss full = "<<double(end-start)<<"\n";

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);

    


	//gauss eml col
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	gauss_elim_col_pivoting(A_1,u);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*x

	back_subs(A_1,b_1);//now b_1=x
	
	end=clock();
	std::cout<<"time_gauss col = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  
	std::cout<<"time_gauss col = "<<double(end-start)<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);

	std::cout<<"\n\n\n\n\n";
}

void exercise_2_1()
{
	int N=100;// size of A
	//initialize A b
	vector<vector<double>> A(N,vector<double> (N)); vector<double> b(N);
	for (int i = 0; i < N-1; i++)
	{
		A[i][i]=10;
		A[i+1][i]=1;
		A[i][i+1]=1;
	}
	A[N-1][N-1]=10;
	
	auto seed=time(0);
	srand(seed);
	for (int i = 0; i < N; i++)
	{
		b[i]=rand()%20+1;
	}
	
	vector<vector<double>> A_1=A; vector<double> b_1=b; //copy otherwise change A b values

	//cholesky
	start=clock();
	cholesky_decomp(A_1);

	forward_subs(A_1,b_1);//now b=L^T*x

	back_subs(A_1,b_1);//now b=x

	end=clock();
	std::cout<<"time_cholesky = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n"; 

	std::cout<<"x^T= ";
	print_vec(b_1);
 

	//modf_cholesky
	 A_1=A;  b_1=b; //copy otherwise change A b values

	start=clock();
	modified_cholesky_decomp(A_1);

	forward_subs1(A_1,b_1);//now b=D*L^T*x

	diag_solve(A_1,b_1);//now b=L^T*x

	back_subs1(A_1,b_1);//now b=x

	end=clock();
	std::cout<<"time_modf_cholesky = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	std::cout<<"\n\n\n\n\n";

}

void exercise_2_2()
{
	int N=40;// size of A
	//initialize A b
	vector<vector<double>> A(N,vector<double> (N)); vector<double> b(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j]=1.0/(i+j+1);
		}
		
	}
	
	for (int i = 0; i < N; i++)
	{
		b[i]=0;
		for (int j = 0; j < N; j++)
		{
			b[i]+=1.0/(i+j+1);
		}
		
	}
	
	
	vector<vector<double>> A_1=A; vector<double> b_1=b; //copy otherwise change A b values

	//cholesky
	start=clock();
	cholesky_decomp(A_1);

	forward_subs(A_1,b_1);//now b=L^T*x

	back_subs(A_1,b_1);//now b=x

	end=clock();
	std::cout<<"time_cholesky = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n"; 

	std::cout<<"x^T= ";
	print_vec(b_1);
 

	//modf_cholesky
	 A_1=A;  b_1=b; //copy otherwise change A b values

	start=clock();
	modified_cholesky_decomp(A_1);

	forward_subs1(A_1,b_1);//now b=D*L^T*x

	diag_solve(A_1,b_1);//now b=L^T*x

	back_subs1(A_1,b_1);//now b=x

	end=clock();
	std::cout<<"time_modf_cholesky = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	std::cout<<"\n\n\n\n\n";
}

void exercise_3_1()
{
	int N=100;// size of A
	//initialize A b
	vector<vector<double>> A(N,vector<double> (N)); vector<double> b(N);
	for (int i = 0; i < N-1; i++)
	{
		A[i][i]=10;
		A[i+1][i]=1;
		A[i][i+1]=1;
	}
	A[N-1][N-1]=10;
	auto seed=time(0);
	srand(seed);
	for (int i = 0; i < N; i++)
	{
		b[i]=rand()%20+1;
	}

	vector<vector<double>> A_1=A; vector<double> b_1=b; //copy otherwise change A b values

	//gauss eml
	start=clock();

	gauss_elim(A_1);// now  LU in A

	forward_subs1(A_1,b_1);// now b_1=Ux=y

	back_subs(A_1,b_1);//now b_1=x

	end=clock();
	std::cout<<"time_gauss = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);



	//gauss eml full
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	vector<int> u(N-1);	vector<int> v(N-1);
	gauss_elim_full_pivoting(A_1,u,v);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*Q^-1*x

	back_subs(A_1,b_1);//now b_1=Q^-1*x

	vector_qb(v,b_1);

	end=clock();
	std::cout<<"time_gauss full = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);




	//gauss eml col
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	gauss_elim_col_pivoting(A_1,u);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*x

	back_subs(A_1,b_1);//now b_1=x
	
	end=clock();
	std::cout<<"time_gauss full = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);

	std::cout<<"\n\n\n\n\n";

}

void exercise_3_2()
{

	int N=40;// size of A
	//initialize A b
	vector<vector<double>> A(N,vector<double> (N)); vector<double> b(N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			A[i][j]=1.0/double(i+j+1);
		}
		
	}
	
	for (int i = 0; i < N; i++)
	{
		b[i]=0;
		for (int j = 0; j < N; j++)
		{
			b[i]+=1.0/double(i+j+1);
		}
		
	}

	vector<vector<double>> A_1=A; vector<double> b_1=b; //copy otherwise change A b values

	//gauss eml
	start=clock();

	gauss_elim(A_1);// now  LU in A

	forward_subs1(A_1,b_1);// now b_1=Ux=y

	back_subs(A_1,b_1);//now b_1=x

	end=clock();
	std::cout<<"time_gauss = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);



	//gauss eml full
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	vector<int> u(N-1);	vector<int> v(N-1);
	gauss_elim_full_pivoting(A_1,u,v);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*Q^-1*x

	back_subs(A_1,b_1);//now b_1=Q^-1*x

	vector_qb(v,b_1);

	end=clock();
	std::cout<<"time_gauss full = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);




	//gauss eml col
	 A_1=A;  b_1=b; //copy otherwise change A b values
	start=clock();

	gauss_elim_col_pivoting(A_1,u);// now  LU in A

	vector_pb(u,b_1);//now b_1=Pb

	forward_subs1(A_1,b_1);// now b_1=U*x

	back_subs(A_1,b_1);//now b_1=x
	
	end=clock();
	std::cout<<"time_gauss full = "<<double(end-start)/CLOCKS_PER_SEC<<"s"<<"\n";  

	std::cout<<"x^T= ";
	print_vec(b_1);

	for (int i = 0; i < N; i++)
	{
		b_1[i]-=1;
	}

	std::cout<<"difference= ";
	print_vec(b_1);

	std::cout<<"\n\n\n\n\n";
}
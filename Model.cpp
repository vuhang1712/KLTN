#include "Model.h"

//v - tong so o vuong
//species - tap hop cac loai
void Model(int s, int v, vector<int> k, vector<vector<int>> a, vector<vector<int>> delta) {
	try {
		IloEnv env;
		IloModel model(env);
		float m = v * v + 1;

		cout << "Creating the variables" << endl;

		//x[i] variables - x[i] = 1 neu o i duoc chon
		IloNumVarArray x(env);
		IloNumVarArray y(env);
		IloNumVarArray z(env);

		for (int i = 0; i < v; i++)
			x.add(IloNumVar(env, 0, 1, ILOINT));

		for (int i = 0; i < v * v; i++)
			y.add(IloNumVar(env, 0, 1, ILOINT));

		for (int i = 0; i < v; i++)
			z.add(IloNumVar(env, 0, v * v, ILOINT));

		//objective function
		cout << "Creating objective function" << endl;
		IloExpr sumOfX(env);

		for (int i = 0; i < v; i++)
			sumOfX += x[i];

		model.add(IloMinimize(env, sumOfX));

		//constraints
		cout << "Creating constraints:" << endl;

		//so o duoc chon trong khu bao ton >= so o chua loai s
		for (int s = 0; s < k.size(); s++) {
			IloExpr sumOfDelta(env);
			for (int i = 0; i < v; i++)
				sumOfDelta += delta[s][i] * x[i];
			model.add(sumOfDelta >= k[s]);
		}

		//neu o j duoc chon, co toi da 4 cung dan vao dinh j
		for (int j = 0; j < v; j++) {
			IloExpr sumOfY(env);
			for (int i = 0; i < v; i++) {
				if (a[i][j] == 1)
					sumOfY += y[i * v + j];
			}
			model.add(sumOfY <= 4 * x[j]);
		}

		//neu o i duoc chon, co toi da 1 cung xuat phat tu i
		for (int i = 0; i < v; i++) {
			IloExpr sumOfY(env);
			for (int j = 0; j < v; j++) {
				if (a[i][j] == 1)
					sumOfY += y[i * v + j];
			}
			model.add(sumOfY <= x[i]);
		}

		//so canh = so dinh - 1
		IloExpr sumOfEdge(env);
		IloExpr sumOfVertex(env);

		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++)
				sumOfEdge += y[i * v + j];
			sumOfVertex += x[i];
		}
		model.add(sumOfEdge == sumOfVertex - 1);

		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
				if (i != j) {
					model.add(z[j] >= z[i] - m * (1 - y[i * v + j]));
					model.add(y[i * v + j] + y[j * v + i] <= 1);
					model.add(y[i * v + j] <= a[i][j]);
				}
			}
		}

		for (int i = 0; i < v; i++) {
			model.add(y[i * v + i] == 0);
		}

		cout << "End of model creating!" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "Begin to solve the model." << endl;

		IloCplex cplex(env);
		cplex.extract(model);
		cplex.exportModel("recourse.lp");
		if (cplex.solve()) {
			//cout << cplex.getStatus() << endl;

			cout << "------------------------------------" << endl;
			cout << "The sol is: " << endl;
			cout << "optimal value is " << cplex.getObjValue() << endl;

			cout << "------------------------------------" << endl;
			for (int i = 0; i < v; i++)
			{
				cout << "x" << i << ": " << cplex.getValue(x[i]) << endl;
			}

			cout << "------------------------------------" << endl;
			cout << "Ma tran y:" << endl;
			for (int i = 0; i < v; i++)
			{
				for (int j = 0; j < v; j++)
				{
					cout << cplex.getValue(y[i * v + j]) << " ";
				}
				cout << endl;
			}
		}
		else {
			cout << "Cannot solve";
		}

		cplex.clear();
		env.end();

	}
	catch (IloException& e) {
		cerr << "CPLEX found the following exception: " << e << endl;
		e.end();
	}
	catch (exception& e) {
		std::exception_ptr p = std::current_exception();
	}
}
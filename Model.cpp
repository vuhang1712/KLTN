#include "Model.h"

//In cac dinh ke cua dinh j
vector<int> adjacent(int v, int j) {
	vector<int> adj;
	for (int i = 0; i < v; i++)
		if (abs(i - j) == 1 || abs(i - j) == sqrt(v))
			adj.push_back(i);
	return adj;
}

//v - tong so o vuong
//species - tap hop cac loai
void Model(int s, int v, vector<int> k, vector<vector<int>> y, vector<vector<int>> delta) {
	try {
		IloEnv env;
		IloModel model(env);
		float m = INFINITY;

		cout << "Creating the variables" << endl;

		//x[i] variables - x[i] = 1 neu o i duoc chon
		IloNumVarArray x(env);
		for (int i = 0; i < v; i++)
			x.add(IloNumVar(env, 0, 1, ILOINT));

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
				sumOfDelta += (delta[s][i] * x[i]);
			model.add(sumOfDelta >= k[s]);
		}

		//neu o j duoc chon, co toi da 4 cung dan vao dinh j
		for (int j = 0; j < v; j++) {
			vector<int> adj = adjacent(v, j);
			IloExpr sumOfY(env);
			for (int i = 0; i < adj.size(); i++) {
				sumOfY += y[i][j];
			}
			model.add(sumOfY <= 4 * x[j]);
		}

		//neu o i duoc chon, co toi da 1 cung xuat phat tu i
		for (int i = 0; i < v; i++) {
			vector<int> adj = adjacent(v, i);
			IloExpr sum(env);
			for (int j = 0; j < adj.size(); j++) {
				sum += y[i][j];
			}
			model.add(sum <= x[i]);
		}

		//so canh = so dinh - 1
		for (int i = 0; i < v; i++) {
			IloExpr sumOfEdge(env);
			IloExpr sumOfVertex(env);
			for (int j = 0; j < v; j++)
				sumOfEdge += y[i][j];
			sumOfVertex += x[i];
			model.add(sumOfEdge == sumOfVertex - 1);
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
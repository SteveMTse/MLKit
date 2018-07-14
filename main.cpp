// #include "Type.hpp"
// #include "Matrix.hpp"
// #include "Tools.hpp"
#include "MLKit.hpp"

double cast(String arg) {
    return stod(arg.c_str());
}

triplet<int> tri_test() {
    return {1,2,3};
}

template<typename T, typename L>
class linear: public generic_model<T, L> {
    public:
        linear() {}

        
        void fit(Matrix<T>& X, Matrix<L>& Y) {
            this -> a = 5;
        }

        void show() {
            cout<<this -> a<<endl;
        }
};

int main(int argc, char* argv[]) {

    // double b[3][3] = {{1,1,1}, {1,1,1}, {1,1,1}};
    // double** c = new double*[3];
    // for(int i = 0 ; i < 3 ; i++) {
    //     c[i] = new double[3];
    //     for(int j = 0 ; j < 3 ; j++) {
    //       c[i][j] = 2;
    //     }
    // }
    // Matrix<double> A = Matrix<double>(a, 3, 3);
    // Matrix<double> A = Matrix<double>({{1,2,3,4,5,6,7,8,9,10}, {11,12,13,14,15,16,17,18,19,20}, {21,22,23,24,25,26,27,28,29,30}, {31,32,33,34,35,36,37,38,39,40}});
    // Matrix<double> B = Matrix<double>({{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,1}});
    // Matrix<double, 3, 3> B = Matrix<double, 3, 3>(b);
    // Matrix<double, 3, 3> C = Matrix<double, 3, 3>(c);
    // Matrix<double> A = Matrix<>
    // A.show();
    // cout<<endl;
    // B.show();
    // cout<<endl;

    // auto D = A.transpose();
    // D.show();
    // C.show();
    // cout<<A[1][1]<<endl;
    // auto D = A * B;
    // D.show();
    // delete [] c;

    // Matrix<double> v = Matrix<double>({{1,2,3},{1,2,3},{1,2,3}});
    // Matrix<double> M1 = Matrix<double>({{1,1,1},{1,1,1},{1,1,1}});
    // Matrix<double> M2 = Matrix<double>({{2,2,2},{2,2,2},{2,2,2}});
    // v.show();
    // cout<<endl;
    // M1.show();
    // cout<<endl;
    // M2.show();
    // cout<<endl;

    // auto D = v * (M1 * M2);
    // D.show();

    // auto D = vector.transpose();
    // auto V = D * matrix;
    // V.show();
    // auto D = matrix * (vector.transpose());
    // auto D = (vector.transpose()) * matrix;
    // D.show();

    // ifstream data;
    // data.open("semeion.data.txt");
    // String buffer = "";

    // char a = 'a';

    // buffer += "asdasdasdasd";
    // buffer += "23423424";

    // cout<<buffer<<endl;

    // triplet<int, int, int> a = {1,2,3};

    // a.show();

    // auto a = buffer.to_number();
    // a.show();
    // String str = String("asdasdasd");
    // String str = "asdasdasdasd";
    // String str = String("");
    // str = "asdasdasdasdas";
    // cout<<str[3]<<endl;
    // printf("%s", str.c_str());
    // cout<<str<<endl;
    // cout<<typeid("asdasdasd").name()<<endl;
    // string str = "asdasdasd";

    // vector<vector<String>> matrix;

    // while(readline(data, buffer)){
    //     matrix.push_back(buffer.split());
    // }

    // vector<int> a = vector<int>({1,2,3,4});
    // cout<<sum<int>({10,12,3,1})<<endl;

    // String s2 = "qw eq we qwe qwe ";
    // cout<<s2<<endl;

    // for(auto && item : s2) {
    //     cout<<item<<"/ ";
    // }
    // cout<<endl;

    // auto str_list = s2.split();
    // for(auto&& item : s2.split()) {
    //     cout<<item<<", ";
    // }
    // cout<<endl;

    // vector<String> a;
    // String buff = "1.012 2.012 3.012";
    // for(char i = '1' ; i <= '5' ; i++) {
    //     buff += i;
    //     a.push_back(buff);
    //     a[i - '1'] += ".16";
    // }

    // auto a = buff.split(3);
    // vector_print<String>(a);
    // auto lst = strlist_to_numlist<double>(a);
    // vector_print<double>(lst, 2);

    // data.close();

    // Linkedlist<int> a = Linkedlist<int>({1,2,3,4});
    // a.show();
    // a.add(0,0);
    // a.show();
    // a.add(100, 2);
    // a.show();
    // a.remove(1);
    // a.show();
    // while(a.size() != 0) {
    //     cout<<"OK: ";
    //     cout<<a[0]<<endl;
    //     a.pop_front();
    // }
    
    // String s = "123.45";
    // cout<<cast(s)<<endl;
    // auto matrix = data_generator<double>("semeion.data.txt", ' ', cast);
    Cast<double> cfd = Cast<double>({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'}, "stod");
    Cast<int> cfi = Cast<int>({'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'}, "stoi");
    auto train_x = data_generator<double>("semeion.data.txt", ' ', cfd, 0, 256);
    auto train_y = data_generator<int>("semeion.data.txt", ' ', cfi, 256, 10);
    LinearRegression<double, int> lm = LinearRegression<double, int>();
    lm.fit(train_x, train_y);
    // lm.show();
    // auto dim_x = train_x.dim();
    // auto dim_y = train_y.dim();
    // dim_x.show();
    // dim_y.show();
    // dim.show();
    // dim.show();
    // cout<<cf.cast("123.45")<<endl;

    // auto a = tri_test();
    // a.show();

    return 0;
}

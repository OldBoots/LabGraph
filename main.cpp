#include <QCoreApplication>
#include <QtGlobal>
#include <iostream>

struct Adges{
    int v1;
    int v2;
    int s;
};

int max_index_vertex(QVector <Adges> vec_adges){
    int max_index = 0;
    for (int i = 0; i < vec_adges.size(); i++){
        if(max_index < vec_adges[i].v1){
            max_index = vec_adges[i].v1;
        }
        if(max_index < vec_adges[i].v2){
            max_index = vec_adges[i].v2;
        }
    }
    return max_index;
}

int edge_search(int v1, int v2, QVector <Adges> vec_adges){
    if(v1 == v2){
        return 0;
    }
    for(int i = 0; i < vec_adges.size(); i++){
        if(v1 == vec_adges[i].v1 && v2 == vec_adges[i].v2){
            return vec_adges[i].s;
        } else if(v1 == vec_adges[i].v2 && v2 == vec_adges[i].v1){
            return vec_adges[i].s;
        }
    }
    return -1;
}

void show_iteration(QVector <int> vec_d){
    std::cout << "old\t";
    for(int i = 0; i < vec_d.size(); i++){
        if(vec_d.size() / 2 == i){ std::cout << std::endl << "new\t"; }
        std::cout << vec_d[i] << "\t";
    }
    std::cout << std::endl << "Di\t";
    for(int i = 0; i < vec_d.size() / 2; i++){
        std::cout << "D"<< i << "\t";
    }
    std::cout << std::endl << std::endl;
}

int min_search(QVector <int> &vec_sum, int &index, bool &found){
    int min = -1;
    for(int i = 0; i < vec_sum.size(); i++){
        if(min == -1 && vec_sum[i] != -1){
            min = vec_sum[i];
            index = i;
        } else if (vec_sum[i] < min && vec_sum[i] != -1){
            min = vec_sum[i];
            index = i;
        }
    }
    vec_sum.clear();
    if(min != -1){
        found = true;
    } else {
        found = false;
    }
    return min;
}

int sum(int a, int b){
    if(a != -1 && b != -1){
        return a + b;
    }
    return -1;
}

void old_new(QVector <int> &vec_d){
    for(int i = 0; i < vec_d.size() / 2; i++){
        qSwap(vec_d[i], vec_d[i + vec_d.size() / 2]);
    }
}

void init_graph(QVector <Adges> &vec_adges){
    Adges t;
    QVector <int> ttt;
    ttt << 0 << 1 << 4;
    ttt << 0 << 5 << 1;
    ttt << 0 << 6 << 6;
    ttt << 1 << 2 << 3;
    ttt << 1 << 4 << 2;
    ttt << 1 << 5 << 2;
    ttt << 2 << 4 << 4;
    ttt << 2 << 3 << 3;
    ttt << 3 << 4 << 1;
    ttt << 3 << 6 << 2;
    ttt << 4 << 6 << 1;
    ttt << 4 << 5 << 1;
    for(int i = 0; i < ttt.size(); i+= 3){
        t.v1 = ttt[i];
        t.v2 = ttt[i + 1];
        t.s = ttt[i + 2];
        vec_adges << t;
        std::cout << t.v1 << " " << t.v2 << " " << t.s << std::endl;
    }
    std::cout << std::endl;
}

struct Path{
    int index_d;
    int v1;
    int v2;
};

void show_path(QVector <Path> vec_path){
    vec_path[0].index_d = 0;
    std::cout << "D" << 0 << ")\t(" << 0 << "-" << 0 << ")" << std::endl;
    for(int i = 1, index; i < vec_path.size(); i++){
        index = i;
        std::cout << "D" << i << ")\t";
        while (index != 0) {
            std::cout << "(" << vec_path[index].v1 << "-" << vec_path[index].v2 << ")";
            index = vec_path[index].index_d;
            if(index != 0){
                std::cout << " <- ";
            }
        }
        std::cout << std::endl;
    }
}



int main()
{
    QVector <Adges> vec_adges;
    QVector <int> vec_d;
    QVector <Path> vec_path;
    QList <QString> list_adges;
    QList <QString> list_vertex;
    Path log;
    init_graph(vec_adges);
    int n = max_index_vertex(vec_adges) + 1;
    vec_d.resize(n * 2, -1);
    vec_path.resize(n);
    vec_d[0] = vec_d[n] = 0;
    int count = 1, adge_c, index;
    QVector <int> vec_sum;
    bool found;
    while(1){
        for(int i = 1; i < n; i++){
            for(int j = 0; j < n; j++){
                adge_c = edge_search(i, j, vec_adges);
                list_adges << QString::number(i) + " " + QString::number(j);
                vec_sum << sum(vec_d[j + n], adge_c);
            }
            vec_d[i] = min_search(vec_sum, index, found);
            if(found){
                list_vertex = list_adges[index].split(" ");
                log.index_d = index;
                log.v1 = list_vertex[0].toInt();
                log.v2 = list_vertex[1].toInt();
                if (log.v1 != log.v2){
                    vec_path[i] = log;
                }
            }
            if(vec_d[i] == vec_d[i + n]){
                count++;
            }
            list_adges.clear();
        }
        if(count == n){ break; }
        old_new(vec_d);
        show_iteration(vec_d);
        count = 1;

    }
    show_iteration(vec_d);
    show_path(vec_path);
    return 0;
}

#ifndef GENERATEPATH_H
#define GENERATEPATH_H
#include <QVector>

//生成路径
class GeneratePath
{
private:
    QVector<QVector<int*> > dfs_res;       //存路的向量
    QVector<int*> temp_vector;
    int dirctions[4][2] = { {0,-1},{0,1},{-1,0},{1,0} };        //上下左右移动的距离

    //检查此位置是否可以走
    int check(int x, int y, int(*my_map)[15])
    {
        if (x < 0 || y < 0 || x >= 12 || y >= 15 || (my_map[x][y] != 6 && my_map[x][y] != 4 && my_map[x][y] != 5))
            return 0;

        return 1;
    }

    //深度优先搜索
    void dfs(int i, int j, int(*my_map)[15])
    {
        temp_vector.push_back(new int[2]{ i,j });

        for (int k = 0; k < 4; k++)
        {
            int x = i + dirctions[k][0];
            int y = j + dirctions[k][1];

            if (check(x, y, my_map))
            {
                if (my_map[x][y] == 6)
                {
                    temp_vector.push_back(new int[2]{ x,y });
                    dfs_res.push_back(temp_vector);
                    temp_vector.pop_back();
                }
                else
                {
                    my_map[x][y] = -1;  // 标记当前位置为已访问
                    dfs(x, y, my_map);
                    my_map[x][y] = 4;  // 恢复当前位置为可走
                }
            }
        }

        temp_vector.pop_back();
    }

    //5 起点 6终点 4可以走的路
    void find_road(int(*my_map)[15])
    {
        dfs_res.clear();
        temp_vector.clear();

        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                if (my_map[i][j] == 5)
                {
                    dfs(i, j, my_map);
                }
            }
        }
    }
public:
    QVector<QVector<int*> > getPathVec(int(*my_map)[15])    //生成路径并返回
    {
        find_road(my_map);
        return dfs_res;
    }
};

#endif // GENERATEPATH_H

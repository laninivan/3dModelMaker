#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cstdlib>
#include <vector>


#ifndef TRIANGULATION_ARRAY
#define TRIANGULATION_ARRAY

class TriangulationArray {
public:
    
    bool isclockwiseOrCounterclockwise(int n, glm::vec2 VertexMas[])
    {
            double min_x =1000, min_y = 1000;
            int extremeVertex = -1;
            for (int i = 0; i < n; i++)
            {
                if (VertexMas[i].x < min_x)
                    min_x = VertexMas[i].x;
                if (VertexMas[i].x == min_x && VertexMas[i].y < min_y)
                {
                    extremeVertex = -i;
                    min_y = VertexMas[i].y;
                }
            }

            if (extremeVertex == 0)
            {
                return ((cross_prod(VertexMas[0], VertexMas[1], VertexMas[n - 1]) < 0) ? true : false);
            }
            else if (extremeVertex == n - 1)
            {
                return ((cross_prod(VertexMas[n - 1], VertexMas[0], VertexMas[n - 2]) < 0) ? true : false);
            }
            else
            {
                return ((cross_prod(VertexMas[extremeVertex], VertexMas[extremeVertex+1], VertexMas[extremeVertex-1]) < 0) ? true : false);
            }
    }
    
    bool isPointInTriangle(int n, glm::vec2 VertexMas[], glm::vec2 first, glm::vec2 second, glm::vec2 third)
    {
        double a, b, c;
        for (int i = 0; i < n; i++)
        {
            if (VertexMas[i] != first && VertexMas[i] != second && VertexMas[i] != third)
            {
                a = cross_prod(VertexMas[i], first, second);
                b = cross_prod(VertexMas[i], second, third);
                c = cross_prod(VertexMas[i], third, first);
                if ((a >= 0 && b >= 0 && c >= 0) || (a <= 0 && b <= 0 && c <= 0))
                    return true;
            }
        }
        return false;
    }

    double cross_prod(glm::vec2 first, glm::vec2  second, glm::vec2  third) {
        double x1 = second.x - first.x, x2 = third.x - first.x,
            y1 = second.y - first.y, y2 = third.y - first.y;
        return (x1 * y2 - x2 * y1);
    }

     std::vector<glm::vec2>  triangulate(int n, glm::vec2 VertexMas[])
    {
        double prod;
        std::vector<glm::vec2> triangles;
        bool clockwiseOrCounter = isclockwiseOrCounterclockwise(n, VertexMas);
        
        for (int i = 0; i < n+1; i++)
        {
            if (n==3)
            {    
                triangles.push_back(VertexMas[0]);
                triangles.push_back(VertexMas[1]);
                triangles.push_back(VertexMas[2]);   
                break;
            }
            if (i == n - 1)
            {               
                 prod = cross_prod(VertexMas[i - 1], VertexMas[i], VertexMas[0]);
                if (prod < 0 && clockwiseOrCounter || prod > 0 && !clockwiseOrCounter)
                {
                    if (!isPointInTriangle(n, VertexMas, VertexMas[i - 1], VertexMas[i], VertexMas[0]))
                    {
                        triangles.push_back(VertexMas[i - 1]);
                        triangles.push_back(VertexMas[i]);
                        triangles.push_back(VertexMas[0]);

                        for (int j = i; j < n - 1; j++)
                        {
                            VertexMas[j] = VertexMas[j + 1];
                        }
                            n--;
                    }                   
                }
                i = -1;
                
            }
            else if (i == 0)
            {              
                prod = cross_prod(VertexMas[n - 1], VertexMas[0], VertexMas[1]);
                if (prod < 0 && clockwiseOrCounter || prod > 0 && !clockwiseOrCounter)
                {
                    if (!isPointInTriangle(n, VertexMas, VertexMas[n - 1], VertexMas[0], VertexMas[1]))                   
                    {
                        triangles.push_back(VertexMas[n - 1]);
                        triangles.push_back(VertexMas[0]);
                        triangles.push_back(VertexMas[1]);

                        for (int j = i; j < n - 1; j++)
                        {
                            VertexMas[j] = VertexMas[j + 1];
                        }
                        i--;
                        n--;
                    }
                }
            }
            else
            {
                prod = cross_prod(VertexMas[i - 1], VertexMas[i], VertexMas[i+1]);
                if (prod < 0 && clockwiseOrCounter || prod > 0 && !clockwiseOrCounter)
                {
                    if (!isPointInTriangle(n, VertexMas, VertexMas[i - 1], VertexMas[i], VertexMas[i+1]))
                    {
                        triangles.push_back(VertexMas[i - 1]);
                        triangles.push_back(VertexMas[i]);
                        triangles.push_back(VertexMas[i+1]);

                        for (int j = i; j < n - 1; j++)
                        {
                            VertexMas[j] = VertexMas[j + 1];
                        }
                        n--;
                        i--;
                    }
                }
            }

        }
        return triangles;
    }
};
#endif 
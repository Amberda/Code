template<class T>
class my_Queue
{
public:
      my_Queue()
      {}
      void Push(T node)
      {
            s1.push(node);
      }
      T* Pop()
      {
            if (s2.size() <= 0)
            {
                  if (s1.size() > 0)
                  {
                        T top = s1.top();
                        s1.pop();
                        s2.push(top);
                  }
            }
            T res = s2.top();
            s2.pop();
            return res;
      }
      ~my_Queue()
      {}
private:
      stack<T> s1;
      stack<T> s2;
};

class Solution {
public:
      bool isValid(string s) {
            stack<char> s1;
            size_t  size = s.size();
            for (size_t i = 0; i < size; i++)
            {
                  if (s[i] == '(' || s[i] == '[' || s[i] == '{')
                        s1.push(s[i]);
                  else if (s[i] == ')' || s[i] == ']' || s[i] == '}')
                  {
                        if (!s1.empty())
                        {
                              char top = s1.top();
                              if (s[i] == ')' &&top == '(' || s[i] == ']'&&top == '[' || s[i] == '}'&&top == '{')
                                    s1.pop();
                              else
                                    return false;
                        }
                        else
                              return false;
                  }
            }
            if (!s1.empty())
                  return false;
            else
                  return true;
      }

};

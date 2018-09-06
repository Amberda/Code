struct TrueType
{
      bool Get()
      {
            return true;
      }
};
struct FalseType
{
      bool Get()
      {
            return false;
      }
};
template<class T>
struct TypeTraits
{
      typedef FalseType IsPod;
};
template<>
struct TypeTraits<int>
{
      typedef TrueType IsPod;
};
template<>
struct TypeTraits<double>
{
      typedef TrueType IsPod;
};
template<>
struct TypeTraits<string>
{
      typedef TrueType IsPod;
};
template<class T>
T Add(T a, T b)
{
      if (TypeTraits<T>::IsPod().Get())
            return a + b;
      else
            return T();
}

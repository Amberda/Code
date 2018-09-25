class Signalson
{
public:
      static Signalson* Get()
      {
            lock();
            if (_s == NULL)
                  _s = new Signalson();
            unlock();
            return _s;
      }
private:
      Signalson()
      {}
      static Signalson* _s;
};
Signalson* Signalson::_s = NULL;

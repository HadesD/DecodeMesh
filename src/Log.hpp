#ifndef LOG_HPP
#define LOG_HPP

#include <QDebug>

class Log
{
  public:
    Log();
};

#define LOG(...) qDebug() << __VA_ARGS__

#if defined(QT_DEBUG)
# define LOG_DEBUG(...) LOG(__VA_ARGS__)
#else
# define LOG_DEBUG(...) void(0)
#endif

#endif // LOG_HPP

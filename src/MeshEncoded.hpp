#ifndef MESHENCODED_HPP
#define MESHENCODED_HPP

#include <QObject>
#include <QFile>

class MeshEncoded : public QObject
{
    Q_OBJECT

  private:
    typedef struct _HeaderInfo
    {
      uchar ukn1[0x10];
      char type;
      uchar ukn[0x50-0x1];
    } HeaderInfo;

  public:
    MeshEncoded(const QString& fileName);
    ~MeshEncoded();

  public:
    bool open(const QIODevice::OpenMode mode);

  private:
    const QString& m_fileName;
    QFile m_hFile;
    HeaderInfo* m_headerInfo;
};

#endif // MESHENCODED_HPP

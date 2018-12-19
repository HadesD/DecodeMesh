#include "MeshEncoded.hpp"

#include "Log.hpp"

MeshEncoded::MeshEncoded(const QString& fileName) :
  QObject(),
  m_fileName(std::move(fileName))
{
}

MeshEncoded::~MeshEncoded()
{
  m_hFile.unmap(reinterpret_cast<uchar*>(m_headerInfo));
  m_hFile.close();
}

bool MeshEncoded::open(const QIODevice::OpenMode mode)
{
//  LOG("Openning:" << m_fileName);

  m_hFile.setFileName(m_fileName);
  if (!m_hFile.open(mode))
  {
    LOG(m_fileName << ": Can not open");
    return false;
  }

  if (m_hFile.size() < sizeof(HeaderInfo))
  {
    LOG(m_fileName << ": Error size");
    return false;
  }

  m_headerInfo = reinterpret_cast<HeaderInfo*>(
        m_hFile.map(0, sizeof(HeaderInfo))
        );
  if (!m_headerInfo)
  {
    LOG(m_fileName << ": Map HeaderInfo error");
    return false;
  }

  static constexpr const uchar headerChecksum[] = {
    0x84, 0xCC, 0xFA, 0x75,
    0x9A, 0x9D, 0x3B, 0x6D,
    0x5A, 0xE1, 0xE8, 0x3A,
    0xC6, 0x0E, 0x6C, 0x7B
  };

  if (std::memcmp(headerChecksum, m_headerInfo->ukn1, sizeof(headerChecksum)))
  {
//    LOG_DEBUG(m_fileName << ": Header wrong!");
    return false;
  }

  LOG(m_fileName << m_headerInfo->type);

  return true;
}

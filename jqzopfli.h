#ifndef __JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__
#define __JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__

// Qt lib import
#include <QString>

namespace JQZopfli
{

struct OptimizeResult
{
    bool optimizeSucceed = false;

    int originalSize = 0;
    int resultSize = 0;

    qreal compressionRatio = 0.0;
    int timeConsuming = 0;
};

OptimizeResult optimize(const QString &originalFilePath, const QString &resultFilePath);

}

#endif//__JQLIBRARY_JQZOPFLI_INCLUDE_JQZOPFLI_H__

/*
Copyright Copyright 2016-17 Sacha Schutz

    This file is part of fastQT.

    Foobar is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Foobar is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.

    @author : Pierre Lindenbaum from FastQC <http://www.bioinformatics.babraham.ac.uk/projects/fastqc/>
    @author : Sacha Schutz <sacha@labsquare.org>
    @author : Pierre Marijon <pierre@marijon.fr>
*/
#include "analysisrunner.h"


AnalysisRunner::AnalysisRunner(QObject *parent)
    :QThread(parent)
{

}

AnalysisRunner::AnalysisRunner(const QString &filename, QObject *parent)
    :QThread(parent)
{
    setFilename(filename);
}

AnalysisRunner::~AnalysisRunner()
{
    mAnalysisList.clear();
}

void AnalysisRunner::run()
{

    setStatus(Running);

    QFileInfo fileInfo(mFilename);
    mFileSize = fileInfo.size();

    QIODevice * file = Q_NULLPTR;

    if (fileInfo.suffix() == "gz")
        file = new KCompressionDevice(mFilename, KCompressionDevice::GZip);

    if (fileInfo.suffix() == "bz2")
        file = new KCompressionDevice(mFilename, KCompressionDevice::BZip2);

    if (fileInfo.suffix() == "xz")
        file = new KCompressionDevice(mFilename, KCompressionDevice::Xz);

    if (fileInfo.suffix() == "fastq")
        file = new QFile(mFilename);

    if (file == Q_NULLPTR)
    {
        qDebug()<<Q_FUNC_INFO<<fileInfo.suffix()<< " file is not supported";
        setStatus(Canceled);
        return;
    }

    if (file->open(QIODevice::ReadOnly))
    {
        mSequenceCount = 0;
        mProgression   = 0;

        FastqReader reader(file);

        // pre compute total size for sequencial access .
        emitUpdate(tr("Analysis ..."));
        reader.computeTotalSize();


        mStartTime.start();

        while (reader.next())
        {

            // check if first sequence is valid..Means it's probably a good file
            if (mSequenceCount == 0)
            {
                if (!reader.sequence().isValid())
                {
                    qCritical()<<Q_FUNC_INFO<<"Cannot read sequence. Are you sure it's a Fastq file ?";
                    setStatus(Canceled);
                    return ;
                }
            }


            ++mSequenceCount;
            // this is critcal and can decrease the speed. Send message only 1 sequence / 1000
            if (mSequenceCount % 1000 == 0)
            {
                int percentNow = reader.percentComplete();
                // if percentNow is still null, return empty percent ...
                if ( (percentNow >= mProgression + 5) || (percentNow == 0))
                {
                    mProgression = percentNow;
                    emitUpdate(QString(tr("%1 Sequences procceed ( %2 \% )")).arg(mSequenceCount).arg(mProgression));
                }

            }


            for (Analysis * a : mAnalysisList)
            {
                a->processSequence(reader.sequence());
            }
        }

        mProgression = 100;
        emitUpdate(tr("Complete "));
        setStatus(Finished);

        mDuration = mStartTime.elapsed();


    }

    file->close();
    delete file;


}

void AnalysisRunner::addAnalysis(Analysis *analysis)
{
    mAnalysisList.append(analysis);
}

void AnalysisRunner::setFilename(const QString &filename)
{
    mFilename = filename;
}

void AnalysisRunner::reset()
{
    for (Analysis * a : analysisList())
        a->reset();
}

const QString &AnalysisRunner::filename() const
{
    return mFilename;
}

AnalysisRunner::Status AnalysisRunner::status() const
{
    return mStatus;
}

QString AnalysisRunner::statusString() const
{
    QMetaEnum metaEnum = QMetaEnum::fromType<AnalysisRunner::Status>();
    return metaEnum.valueToKey(mStatus);
}

int AnalysisRunner::progression() const
{
    return mProgression;
}

int AnalysisRunner::sequenceCount() const
{
    return mSequenceCount;
}


quint64 AnalysisRunner::fileSize() const
{
    return mFileSize;
}

QString AnalysisRunner::humanFileSize() const
{
    char unit;
    const char *units [] = {" Bytes", " kB", " MB", " GB"};
    quint64 size = fileSize(); // or whatever

    for (unit=-1; (++unit<3) && (size>1023); size/=1024);

    return QString::number(size, 'f', 1) + units[unit];

}

const QString &AnalysisRunner::lastMessage() const
{
    return mMessage;
}

int AnalysisRunner::duration() const
{
    if (isFinished())
        return mDuration;

    else
        return mStartTime.elapsed();

}





const QVector<Analysis*> &AnalysisRunner::analysisList() const
{
    return mAnalysisList;
}

void AnalysisRunner::emitUpdate(const QString &message)
{
    mMessage = message;
    emit updated(mMessage);
}

void AnalysisRunner::setStatus(AnalysisRunner::Status status)
{
    if (mStatus != status)
    {
        mStatus = status;
        emit statusChanged();
    }

}

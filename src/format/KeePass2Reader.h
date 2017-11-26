/*
 *  Copyright (C) 2017 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef KEEPASSX_KEEPASS2READER_H
#define KEEPASSX_KEEPASS2READER_H

#include <QtGlobal>
#include <QByteArray>
#include <QString>
#include <QCoreApplication>
#include <QScopedPointer>
#include <QIODevice>

#include "format/KeePass2.h"
#include "core/Database.h"
#include "keys/CompositeKey.h"

class BaseKeePass2Reader
{
public:
    BaseKeePass2Reader();

    virtual Database* readDatabase(QIODevice* device, const CompositeKey& key, bool keepDatabase = false) = 0;
    virtual Database* readDatabase(const QString& filename, const CompositeKey& key);

    virtual bool hasError();
    virtual QString errorString();
    virtual void setSaveXml(bool save);
    virtual QByteArray xmlData();
    virtual QByteArray streamKey();
    virtual KeePass2::ProtectedStreamAlgo protectedStreamAlgo() const;

    virtual ~BaseKeePass2Reader();

protected:
    void raiseError(const QString& errorMessage);

    bool m_error;
    QString m_errorStr;

    bool m_saveXml;
    QByteArray m_xmlData;
    QByteArray m_protectedStreamKey;
    KeePass2::ProtectedStreamAlgo m_irsAlgo;
};

class KeePass2Reader : public BaseKeePass2Reader
{
    Q_DECLARE_TR_FUNCTIONS(KeePass2Reader)

public:
    virtual Database* readDatabase(QIODevice* device, const CompositeKey& key, bool keepDatabase = false) override;
    using BaseKeePass2Reader::readDatabase;

    virtual bool hasError() override;
    virtual QString errorString() override;
    virtual QByteArray xmlData() override;
    virtual QByteArray streamKey() override;
    virtual KeePass2::ProtectedStreamAlgo protectedStreamAlgo() const override;

    quint32 version() const;
    BaseKeePass2Reader* reader() const;
private:
    QScopedPointer<BaseKeePass2Reader> m_reader;
    quint32 m_version;
};

#endif // KEEPASSX_KEEPASS2READER_H

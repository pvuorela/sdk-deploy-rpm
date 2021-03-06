#ifndef DEVEL_DEPLOY_RPM_DEPLOYER_H
#define DEVEL_DEPLOY_RPM_DEPLOYER_H

/*
 Copyright (C) 2014 Jolla Oy
 Contact: Jarko Vihriälä <jarko.vihriala@jolla.com>
 All rights reserved.

 You may use this file under the terms of BSD license as follows:

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   * Neither the name of the Jolla Ltd nor the
     names of its contributors may be used to endorse or promote products
     derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <QObject>
#include <QStringList>

#include <Transaction>

class Deployer : public QObject {
    Q_OBJECT

public:
    Deployer(QStringList rpms, bool verbose=false);
    ~Deployer();

public slots:
    void run();
    void onChanged();
    void onItemProgress(const QString &itemID,
            PackageKit::Transaction::Status status,
            uint percentage);
    void onFinished(PackageKit::Transaction::Exit status,
            uint runtime);
    void onErrorCode(PackageKit::Transaction::Error error,
                     const QString &details);
    void onPackage(PackageKit::Transaction::Info info,
                   const QString &packageID,
                   const QString &summary);

private:
    PackageKit::Transaction *tx;

    enum State {
        INITIAL = 0,
        INSTALLING,
        DONE,
    } state;

    QStringList rpms;
    bool verbose_output;
};

#endif /* DEVEL_DEPLOY_RPM_DEPLOYER_H */

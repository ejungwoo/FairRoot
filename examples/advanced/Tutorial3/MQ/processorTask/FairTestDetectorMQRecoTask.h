/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORMQRECOTASK_H
#define FAIRTESTDETECTORMQRECOTASK_H

#include <iostream>
#include <sstream>
#include <array>

#include "TMath.h"
#include "TClonesArray.h"

#include "FairRootManager.h"
#include "FairMQLogger.h"
#include "FairMQProcessorTask.h"
#include "FairMQMessage.h"

#include "FairTestDetectorRecoTask.h"
#include "FairTestDetectorPayload.h"
#include "FairTestDetectorHit.h"
#include "FairTestDetectorDigi.h"

template<typename TIn, typename TOut, typename TPayloadIn, typename TPayloadOut>
class FairTestDetectorMQRecoTask : public FairMQProcessorTask
{
  public:
    FairTestDetectorMQRecoTask()
        : fRecoTask()
    {}

    FairTestDetectorMQRecoTask(Int_t /*verbose*/)
        : fRecoTask()
    {}

    FairTestDetectorMQRecoTask(const FairTestDetectorMQRecoTask&) = delete;
    FairTestDetectorMQRecoTask operator=(const FairTestDetectorMQRecoTask&) = delete;

    virtual ~FairTestDetectorMQRecoTask()
    {
        if (fRecoTask.fDigiArray) {
            fRecoTask.fDigiArray->Delete();
            delete fRecoTask.fDigiArray;
        }
        if (fRecoTask.fHitArray) {
            fRecoTask.fHitArray->Delete();
            delete fRecoTask.fHitArray;
        }
    }

    virtual InitStatus Init()
    {
        fRecoTask.SetStreamProcessing(kTRUE);
        fRecoTask.fDigiArray = new TClonesArray("FairTestDetectorDigi");
        fRecoTask.fHitArray = new TClonesArray("FairTestDetectorHit");

        return kSUCCESS;
    }

    virtual void Exec(Option_t* opt = "0");

  private:
    FairTestDetectorRecoTask fRecoTask;
};

// Template implementation of exec in FairTestDetectorMQRecoTask.tpl :
#include "FairTestDetectorMQRecoTaskBin.tpl"
#include "FairTestDetectorMQRecoTaskBoost.tpl"
#include "FairTestDetectorMQRecoTaskFlatBuffers.tpl"
#include "FairTestDetectorMQRecoTaskMsgpack.tpl"
#include "FairTestDetectorMQRecoTaskProtobuf.tpl"
#include "FairTestDetectorMQRecoTaskTMessage.tpl"

#endif /* FAIRTESTDETECTORMQRECOTASK_H */

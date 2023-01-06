#include "RequestHTTP.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

URequestHTTP::URequestHTTP()
{
	HTTP = &FHttpModule::Get();
}

void URequestHTTP::Activate()
{
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HTTPRequest = HTTP->CreateRequest();
	HTTPRequest->SetVerb("GET");
	HTTPRequest->SetHeader("Content-Type", "application/json");
	HTTPRequest->SetURL(URL);
	
	HTTPRequest->OnProcessRequestComplete().BindLambda([&](
		FHttpRequestPtr Request,
		FHttpResponsePtr Response,
		bool bSuccess)
		{
			FString ResponseString;
		
			if (bSuccess)
			{
				ResponseString = Response->GetContentAsString();
			}

			TArray<FMatchResponse> Data;
			FJsonObjectConverter::JsonArrayStringToUStruct(ResponseString, &Data, 0, 0);
		
			Completed.Broadcast(Data, bSuccess);
		});
	
	HTTPRequest->ProcessRequest();
}

URequestHTTP* URequestHTTP::AsyncRequestHTTP(UObject* WorldContextObject, FString URL)
{
	URequestHTTP* Action = NewObject<URequestHTTP>();
	Action->URL = URL;
	Action->RegisterWithGameInstance(WorldContextObject);

	return Action;
}

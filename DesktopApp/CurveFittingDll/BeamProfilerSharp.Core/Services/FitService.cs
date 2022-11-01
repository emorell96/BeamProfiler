using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using BeamProfilerSharp.Core.Models;

namespace BeamProfilerSharp.Core.Services;
public class FitService : IFitService
{
    private readonly HttpClient httpClient;
    private readonly string baseUrl = "http://localhost:9001";// "https://279d1aa6-70f0-4a9c-b20a-51fe8bd1df02.mock.pstmn.io"; // "http://localhost:9001";

    public FitService(HttpClient httpClient)
    {
        this.httpClient = httpClient;
    }

    public async Task RequestFitAsync(FitOptions fitOptions, CancellationToken cancellationToken = default)
    {
        var request = new HttpRequestMessage(HttpMethod.Post, $"{baseUrl}/fit");
        //request.Content = JsonContent.Create(fitOptions, options: new System.Text.Json.JsonSerializerOptions
        //{
        //    PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
        //});
        request.Content = new StringContent(JsonSerializer.Serialize(fitOptions, options: new System.Text.Json.JsonSerializerOptions
        {
            PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
        }));

        var response = await httpClient.SendAsync(request, cancellationToken);

        if(response.IsSuccessStatusCode)
        {

        }
    }
}

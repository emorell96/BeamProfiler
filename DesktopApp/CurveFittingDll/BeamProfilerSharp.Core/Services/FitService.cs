using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Text.Json;
using System.Threading.Tasks;
using BeamProfilerSharp.Core.Models;
using BeamProfilerSharp.Services;

namespace BeamProfilerSharp.Core.Services;
public class FitService : IFitService
{
    private readonly HttpClient httpClient;
    private readonly string baseUrl = "http://localhost:{0}";// "https://279d1aa6-70f0-4a9c-b20a-51fe8bd1df02.mock.pstmn.io"; // "http://localhost:9001";
    private readonly IServerService serverService;

    public FitService(HttpClient httpClient, IServerService serverService)
    {
        this.httpClient = httpClient;
        this.serverService = serverService;
    }

    public async Task<FitResults?> RequestFitAsync(FitOptions fitOptions, CancellationToken cancellationToken = default)
    {
        var request = new HttpRequestMessage(HttpMethod.Post, $"{string.Format(baseUrl, serverService.Port)}/fit")
        {
            //request.Content = JsonContent.Create(fitOptions, options: new System.Text.Json.JsonSerializerOptions
            //{
            //    PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
            //});
            Content = new StringContent(JsonSerializer.Serialize(fitOptions, options: new System.Text.Json.JsonSerializerOptions
            {
                PropertyNamingPolicy = System.Text.Json.JsonNamingPolicy.CamelCase
            }))
        };

        var response = await httpClient.SendAsync(request, cancellationToken).ConfigureAwait(false);

        if(response.IsSuccessStatusCode)
        {
            return await response.Content.ReadFromJsonAsync<FitResults?>(cancellationToken: cancellationToken).ConfigureAwait(false);
        }
        return null;
    }
}

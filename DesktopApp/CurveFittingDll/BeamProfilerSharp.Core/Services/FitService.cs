using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Json;
using System.Text;
using System.Threading.Tasks;
using BeamProfilerSharp.Core.Models;

namespace BeamProfilerSharp.Core.Services;
public class FitService
{
    private readonly HttpClient httpClient;
    private readonly string baseUrl = "http://localhost:9001";

    public FitService(HttpClient httpClient)
    {
        this.httpClient = httpClient;
    }

    public Task RequestFitAsync(FitOptions fitOptions, CancellationToken cancellationToken = default)
    {
        var request = new HttpRequestMessage(HttpMethod.Post, $"{baseUrl}/fit");
        request.Content = JsonContent.Create(fitOptions);

        return httpClient.SendAsync(request, cancellationToken);
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Services;
public class ServerService : IServerService
{
    private Task<int>? _startTask;

    private readonly string _baseUrl = "http://localhost:{0}/{1}";

    private readonly HttpClient _httpClient;

    public ServerService(HttpClient httpClient)
    {
        _httpClient = httpClient;
    }

    public int Port
    {
        get;
        private set;
    } = 9001;

    public void StartServer()
    {
        IPGlobalProperties properties = IPGlobalProperties.GetIPGlobalProperties();
        IPEndPoint[] tcpEndPoints = properties.GetActiveTcpListeners();
        List<int> usedPorts = tcpEndPoints.Select(p => p.Port).ToList<int>();

        while (usedPorts.Contains(Port))
        {
            Port += 1;
        }
        
        _startTask = Task.Run(() => RunServer(Port));
    }

    public async Task StopServerAsync()
    {
        var requestMessage = 
            new HttpRequestMessage(HttpMethod.Get, string.Format(_baseUrl, Port, "close"));
        
        await _httpClient.SendAsync(requestMessage).ConfigureAwait(false);

        await (_startTask ?? Task.CompletedTask).ConfigureAwait(false);
    }

    [DllImport("CurveFittingDll.dll", EntryPoint = "runServer")]
    private static extern int RunServer(int port);
}

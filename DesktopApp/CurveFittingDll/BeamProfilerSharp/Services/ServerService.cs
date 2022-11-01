using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Net.NetworkInformation;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
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
        
        _startTask = Task.Run(() => {
            try
            {
                return RunServer(Port);
            }
            catch
            {
                return 1;
            }
            
            }
        );
    }

    public async Task StopServerAsync()
    {
        var cancellationTokenSource = new CancellationTokenSource();
        cancellationTokenSource.CancelAfter(TimeSpan.FromSeconds(120));
        var requestMessage = 
            new HttpRequestMessage(HttpMethod.Get, string.Format(_baseUrl, Port, "close"));
        try
        {
            await _httpClient.SendAsync(requestMessage, cancellationTokenSource.Token).ConfigureAwait(false);

            await (_startTask ?? Task.CompletedTask).ConfigureAwait(false);
        }
        catch
        {
            return;
        }
        
    }

    [DllImport("CurveFittingDll.dll", EntryPoint = "runServer")]
    private static extern int RunServer(int port);
}

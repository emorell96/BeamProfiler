namespace BeamProfilerSharp.Services;

public interface IServerService
{
    int Port
    {
        get;
    }

    void StartServer();
    Task StopServerAsync();
}
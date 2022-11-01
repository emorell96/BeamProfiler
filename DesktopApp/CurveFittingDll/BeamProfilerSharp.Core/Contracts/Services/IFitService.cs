using BeamProfilerSharp.Core.Models;

namespace BeamProfilerSharp.Core.Services;
public interface IFitService
{
    Task<FitResults?> RequestFitAsync(FitOptions fitOptions, CancellationToken cancellationToken = default);
}
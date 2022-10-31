using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json.Serialization;
using System.Threading.Tasks;

namespace BeamProfilerSharp.Core.Models;
public class Parameter
{
    [JsonPropertyName("value")]
    public double Value
    {
        get; set;
    }

    [JsonPropertyName("hasLowerBound")]
    public bool HasLowerBound
    {
        get; set;
    }

    [JsonPropertyName("lowerBound")]
    public double LowerBound
    {
        get; set;
    }

    [JsonPropertyName("hasUpperBound")]
    public bool HasUpperBound
    {
        get; set;
    }

    [JsonPropertyName("upperBound")]
    public double UpperBound
    {
        get; set;
    }
}

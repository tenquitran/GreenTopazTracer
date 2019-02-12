#pragma once


namespace GreenTopazTracerApp
{
    // Tone mapping algorithm used (if any).
    enum class EToneMapping
    {
        None,       /* No tone mapping. */
        Exposure    /* Exposure algorithm. */
    };
}

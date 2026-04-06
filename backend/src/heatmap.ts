// functions to edit heatmap
<script async
    src="https://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY&loading=async&libraries=visualization&callback=initMap">
</script>

type WeightCoord = [lat: number, lng: number, weight: number];

// Array of exactly 1440 coordinates (one per minute in a 24-hour day)
type CoordForOneDay = WeightCoord[] & { readonly length: 1440 };

function create_coordinates_heatmap(): WeightCoord[] {
    return [];
}

function create_coordinates_for_one_day(): CoordForOneDay {
    return new Array(1440).fill([0, 0, 0]) as CoordForOneDay;
}

function create_heatmap_layer(): void {
    // stub
}
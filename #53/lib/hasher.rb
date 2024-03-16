class Hasher
  def self.fnv1(string, variant: 64)
    prime, offset_basis =
      case variant
      when 32 then [16777619, 2166136261]
      when 64 then [1099511628211, 14695981039346656037]
      else raise ArgumentError, "Variant #{variant}-bit not supported"
      end

    string.each_byte.reduce(offset_basis) do |hash, byte|
      [hash * prime].pack('L').unpack('L')[0] ^ byte
    end
  end
end

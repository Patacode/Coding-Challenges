# frozen_string_literal: true

require 'hasher'

class BloomFilter
  attr_reader :size, :hash_function_count

  def initialize(datasource, epsilon: 0.1)
    line_qty = filesize(datasource)

    @size = required_bit_qty(line_qty, epsilon)
    @hash_function_count = optimal_hash_function_qty(@size, line_qty)
    @bit_array = 0
  end

  def to_i
    @bit_array
  end

  def add(string)
    compute_64bit_fnv1_hashes(string.strip)
      .each { |hash| @bit_array |= compute_index(hash) }
  end

  def include?(string)
    compute_64bit_fnv1_hashes(string.strip)
      .map { |hash| @bit_array & compute_index(hash) }
      .none?(0)
  end

  def save_to_file(filepath)
    cbit_array = @bit_array.clone
    mask = (2**@size) - 1
    byte_size = 8

    mask ^= mask >> byte_size
    offset = byte_size
    File.open("#{filepath}.bf", 'w') do |file|
      while mask.positive?
        file << [(cbit_array & mask) >> (@size - offset)].pack('C')
        mask >>= byte_size
        offset += byte_size
      end
    end
  end

  private

  def filesize(filepath)
    File.open(filepath) do |file|
      file.each_line.count
    end
  end

  def required_bit_qty(elem_qty, epsilon)
    -(elem_qty * Math.log(epsilon) / (Math.log(2)**2)).floor
  end

  def optimal_hash_function_qty(bit_qty, elem_qty)
    (bit_qty / elem_qty.to_f * Math.log(2)).ceil
  end

  def init_bit_array(filepath)
    File.open(filepath) do |file|
      file
        .each_line
        .lazy
        .map { |line| compute_64bit_fnv1_hashes(line.strip) }
        .reduce(0) do |bit_array, hashes|
          hashes.reduce(bit_array) do |cbit_array, hash|
            cbit_array | compute_index(hash)
          end
        end
    end
  end

  def compute_64bit_fnv1(string, offset_basis = nil)
    Hasher.fnv1(string, variant: 64, offset_basis: offset_basis)
  end

  def compute_64bit_fnv1_hashes(string)
    hashes = []
    offset_basis = nil

    @hash_function_count.times do
      new_hash = compute_64bit_fnv1(string, offset_basis)
      offset_basis = new_hash
      hashes << (new_hash % @size)
    end

    hashes
  end

  def compute_index(hash)
    2**hash
  end
end
